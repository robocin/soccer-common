#ifndef SOCCER_COMMON_GLTEXTHELPER_2_1_H
#define SOCCER_COMMON_GLTEXTHELPER_2_1_H

#include <cmath>
#include <QFont>
#include <QPainterPath>
#include "soccer-common/gui/GameVisualizer/GLTessellatorHelper_2_1/GLTessellatorHelper_2_1.h"
#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Utils/Utils.h"

class GLTextHelper_2_1 : public GLTessellatorHelper_2_1 {
  class GlyphBase {
    qreal m_ascent;
    qreal m_descent;
    qreal m_height;
    qreal m_width;
    GLuint m_displayListId;

   public:
    GlyphBase(qreal t_ascent,
              qreal t_descent,
              qreal t_height,
              qreal t_width,
              GLuint t_displayListId) :
        m_ascent(t_ascent),
        m_descent(t_descent),
        m_height(t_height),
        m_width(t_width),
        m_displayListId(t_displayListId) {
    }

    inline qreal ascent() const {
      return m_ascent;
    }

    inline qreal descent() const {
      return m_descent;
    }

    inline qreal height() const {
      return m_height;
    }

    inline qreal width() const {
      return m_width;
    }

    inline GLuint displayListId() const {
      return m_displayListId;
    }
  };

  class Glyph : public GlyphBase {
    GLTessellatorHelper_2_1* m_f;

    inline static GlyphBase
    makeGlyph(GLTessellatorHelper_2_1* f, const QChar& ch, const QFont& font) {
      Q_ASSERT(f != nullptr);
      QPainterPath painterPath;
      QList<QPolygonF> polygons;

      painterPath.addText(0, 0, font, ch);
      polygons = painterPath.toSubpathPolygons();
      bool isEmptyPolygon = polygons.empty();

      if (isEmptyPolygon) { // simulate blank chars with undescore size.
        painterPath.addText(0, 0, font, QChar('_'));
        polygons = painterPath.toSubpathPolygons();
      }

      std::optional<qreal> minX;
      std::optional<qreal> minY;
      std::optional<qreal> maxX;
      std::optional<qreal> maxY;
      std::vector<std::array<GLdouble, 3>> vertices;

      for (const auto& polygon : polygons) {
        for (auto pt : polygon) {
          minX = std::min(minX.value_or(pt.x()), pt.x());
          minY = std::min(minY.value_or(pt.y()), pt.y());

          maxX = std::max(maxX.value_or(pt.x()), pt.x());
          maxY = std::max(maxY.value_or(pt.y()), pt.y());
        }
      }

      TessScopedDrawGuard guard(f, true);
      DisplayListGuard displayGuard(f);
      if (!isEmptyPolygon) {
        for (const auto& polygon : polygons) {
          for (auto pt : polygon) {
            pt /= Const::fontRenderSize;
            vertices.push_back(f->makeTessVertex(pt.x(), -pt.y()));
          }
        }
        TessPolygonGuard polygonGuard(guard.tess());
        for (int i = 0, v = 0; i < polygons.size(); ++i) {
          TessContourGuard tessGuard(guard.tess());
          for (int j = 0; j < polygons[i].size(); ++j, ++v) {
            gluTessVertex(guard.tess(), vertices[v].data(), vertices[v].data());
          }
        }
      }

      qreal ascent = std::abs(*minY) / Const::fontRenderSize;
      qreal descent = std::abs(*maxY) / Const::fontRenderSize;
      qreal height = (*maxY - *minY) / Const::fontRenderSize;
      qreal width = (*maxX - *minX) / Const::fontRenderSize;
      GLuint displayListId = displayGuard.key();

      return GlyphBase(ascent, descent, height, width, displayListId);
    }

   public:
    inline Glyph(GLTessellatorHelper_2_1* f,
                 const QChar& ch,
                 const QFont& font) :
        GlyphBase(makeGlyph(f, ch, font)),
        m_f(f) {
    }

    inline ~Glyph() {
      m_f->glDeleteLists(displayListId(), 1);
    }
  };

  class Glyphs {
    QFont m_font;
    GLTextHelper_2_1* m_f;
    std::map<QChar, std::unique_ptr<Glyph>> m_glyphs;

   public:
    inline Glyphs(GLTextHelper_2_1* f) : m_f(f) {
      Q_ASSERT(f != nullptr);
      m_font.setPixelSize(Const::fontRenderSize);
    }

    inline ~Glyphs() {
    }

    inline void setFont(const QFont& font) {
      m_font = font;
      m_font.setPixelSize(Const::fontRenderSize);
      m_glyphs.clear();
    }

    inline const GlyphBase& operator[](const QChar& ch) {
      auto it = m_glyphs.find(ch);
      if (it == m_glyphs.end()) {
        it = m_glyphs.emplace(ch, std::make_unique<Glyph>(m_f, ch, m_font))
                 .first;
      }
      return *it->second;
    }
  };

  qreal textWidth(const QString& text);
  qreal textHeight(const QString& text);
  qreal textAscent(const QString& text);
  qreal textDescent(const QString& text);

  void putChar(const QChar& ch);

 public:
  enum class HAlign : int { Left, Center, Right };
  enum class VAlign : int { Bottom, Median, Middle, Top };

  GLTextHelper_2_1();
  ~GLTextHelper_2_1();

  inline void drawText(const QString& text,
                       const Vertex& position,
                       qreal size,
                       const QColor& color,
                       qreal angle = 0.0,
                       HAlign hAlign = HAlign::Center,
                       VAlign vAlign = VAlign::Middle) {
    glMatrixMode(GL_MODELVIEW);
    PushPopGuard pushPopGuard(this);
    putColor(color);
    translateZ();
    translateXYScaleAndRotate(position,
                              size,
                              Geometry::radiansToDegrees(angle));

    switch (hAlign) {
      case HAlign::Left: {
        break;
      }
      case HAlign::Center: {
        translateXY(-0.5 * textWidth(text), 0);
        break;
      }
      case HAlign::Right: {
        translateXY(-textWidth(text), 0);
        break;
      }
    }
    switch (vAlign) {
      case VAlign::Bottom: {
        translateXY(0, textDescent(text));
        break;
      }
      case VAlign::Median: {
        break;
      }
      case VAlign::Middle: {
        translateXY(0, -0.5 * textHeight(text));
        break;
      }
      case VAlign::Top: {
        translateXY(0, -textAscent(text));
        break;
      }
    }
    Vertex direction(std::cos(0), std::sin(0));
    for (int i = 0; i < text.size(); ++i) {
      putChar(text[i]);
      if (i + 1 < text.size()) {
        qreal d = glyphs[text[i]].width() + local.spacing;
        translateXY(d * direction.x(), d * direction.y());
      }
    }
  }

 protected:
  void setFont(const QFont& font);
  void setTextSpacing(qreal spacing);

 private:
  Glyphs glyphs;

  struct Local {
    qreal spacing = 0.1;
  } local;

  struct Const {
    static constexpr qreal fontRenderSize = 1000.0;
  };
};

#endif // SOCCER_COMMON_GLTEXTHELPER_2_1_H
