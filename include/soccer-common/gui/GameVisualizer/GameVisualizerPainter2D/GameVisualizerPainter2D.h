#ifndef GAMEVISUALIZERPAINTER2D_H
#define GAMEVISUALIZERPAINTER2D_H

#include "soccer-common/gui/GameVisualizer/GLTextHelper_2_1/GLTextHelper_2_1.h"
#include <QDebug>

class GameVisualizerPainter2D : protected GLTextHelper_2_1 {
  friend class GameVisualizer;

  inline static Polygon removeCollinearPoints(const Polygon& polygon) {
    if (polygon.size() <= 2) {
      if (polygon.size() == 2 && (polygon.front() == polygon.back())) {
        return Polygon({polygon.front()});
      } else {
        return polygon;
      }
    }
    auto areCollinear = [](const Vertex& a, const Vertex& b, const Vertex& c) {
      return qFuzzyIsNull(Geometry2D::cross(a - b, c - b));
    };
    Polygon fixed;
    for (int n = polygon.size(), i = 0; i < n; ++i) {
      while (fixed.size() >= 2) {
        int k = fixed.size();
        if (areCollinear(fixed[k - 1], fixed[k - 2], polygon[i])) {
          fixed.pop_back();
        } else {
          break;
        }
      }
      fixed += polygon[i];
    }
    return fixed;
  }

  struct Local {
    std::optional<GLuint> circleDisplayListId;
  };
  Local local;

 public:
  inline GameVisualizerPainter2D() {
  }

  inline ~GameVisualizerPainter2D() {
    if (local.circleDisplayListId) {
      glDeleteLists(*local.circleDisplayListId, 1);
    }
  }

  using GLTextHelper_2_1::drawText;
  using GLTextHelper_2_1::HAlign;
  using GLTextHelper_2_1::VAlign;

  inline void drawFilledTriangle(const Vertex& a,
                                 const Vertex& b,
                                 const Vertex& c,
                                 const QColor& color) {
    ScopedDrawGuard guard(this, GL_TRIANGLES);
    putColor(color);
    putVertices(a, b, c);
  }

  inline void drawFilledQuad(const Vertex& a,
                             const Vertex& b,
                             const Vertex& c,
                             const Vertex& d,
                             const QColor& color) {
    ScopedDrawGuard guard(this, GL_QUADS);
    putColor(color);
    putVertices(a, b, c, d);
  }

  inline void drawFilledRectangle(const Vertex& topLeft,
                                  const Vertex& bottomRight,
                                  const QColor& color) {
    const auto& rect = QRectF(topLeft, bottomRight);
    drawFilledQuad(rect.topLeft(),
                   rect.topRight(),
                   rect.bottomRight(),
                   rect.bottomLeft(),
                   color);
  }

  inline void
  drawPolygon(Polygon polygon, const QColor& color, qreal thickness) {
    ScopedDrawGuard guard(this, GL_QUAD_STRIP);
    polygon = removeCollinearPoints(polygon);
    if (polygon.size() < 3) {
      qWarning() << "at least 3 distinct points.";
      return;
    }
    if (thickness <= 0) {
      qWarning() << "thickness must be positive.";
      return;
    }

    putColor(color);

    thickness /= 2.0;

    for (int i = 0, n = polygon.size(); i <= n; ++i) {
      const Vertex& a = polygon[i % n];
      const Vertex& b = polygon[(i + 1) % n];
      const Vertex& c = polygon[(i + 2) % n];

      const Vertex& ba(b - a);
      const Vertex& bc(b - c);
      qreal thetab = Geometry2D::angleBetween(ba, bc);
      Vertex vb = Geometry2D::rotateCCW(ba, thetab / 2.0);

      if (qFuzzyIsNull(std::sin(thetab / 2.0))) {
        vb = Vertex();
      } else {
        vb = Geometry2D::resize(vb, thickness / std::sin(thetab / 2.0));
      }

      putVertices(b - vb, b + vb);
    }
  }

  inline void drawFilledConvexPolygon(Polygon polygon, const QColor& color) {
    ScopedDrawGuard guard(this, GL_POLYGON);
    polygon = removeCollinearPoints(polygon);
    if (polygon.size() < 3) {
      qWarning() << "at least 3 distinct points.";
      return;
    }
    putColor(color);
    for (const auto& point : polygon) {
      putVertex(point);
    }
  }

  inline void drawFilledPolygon(Polygon polygon, const QColor& color) {
    TessScopedDrawGuard guard(this);
    putColor(color);
    QVector<std::array<GLdouble, 3>> vertices;
    vertices.reserve(polygon.size());
    for (const auto& point : polygon) {
      vertices.push_back(makeTessVertex(point));
    }

    TessPolygonGuard polygonGuard(guard.tess());
    TessContourGuard tessGuard(guard.tess());
    for (auto& vertex : vertices) {
      gluTessVertex(guard.tess(), vertex.data(), vertex.data());
    }
  }

  inline void
  drawPolyline(Polygon polyline, const QColor& color, qreal thickness) {
    ScopedDrawGuard guard(this, GL_QUAD_STRIP);
    polyline = removeCollinearPoints(polyline);
    if (polyline.size() < 2) {
      qWarning() << "at least 2 distinct points.";
      return;
    }
    if (thickness <= 0) {
      qWarning() << "thickness must be positive.";
      return;
    }
    putColor(color);

    thickness /= 2.0;

    /* first vertex */ {
      const Vertex& a = polyline[0];
      const Vertex& b = polyline[1];
      putVertices(
          a + Geometry2D::resize(Geometry2D::rotateCW90(b - a), thickness),
          a + Geometry2D::resize(Geometry2D::rotateCCW90(b - a), thickness));
    }
    for (int i = 1, n = polyline.size(); i < n - 1; ++i) {
      const Vertex& a = polyline[i - 1];
      const Vertex& b = polyline[i];
      const Vertex& c = polyline[i + 1];

      Vertex ba(b - a);
      Vertex bc(b - c);
      qreal thetab = Geometry2D::angleBetween(ba, bc);
      Vertex vb = Geometry2D::rotateCCW(ba, thetab / 2.0);

      if (qFuzzyIsNull(std::sin(thetab / 2.0))) {
        vb = Vertex();
      } else {
        vb = Geometry2D::resize(vb, thickness / std::sin(thetab / 2.0));
      }

      putVertices(b - vb, b + vb);
    }
    /* last vertex */ {
      const Vertex& a = polyline[polyline.size() - 2];
      const Vertex& b = polyline[polyline.size() - 1];
      putVertices(
          b + Geometry2D::resize(Geometry2D::rotateCW90(b - a), thickness),
          b + Geometry2D::resize(Geometry2D::rotateCCW90(b - a), thickness));
    }
  }

  inline void drawLine(const Vertex& a,
                       const Vertex& b,
                       const QColor& color,
                       qreal thickness) {
    return drawPolyline({a, b}, color, thickness);
  }

  inline void drawArc(const Vertex& origin,
                      qreal innerRadius,
                      qreal outterRadius,
                      qreal theta1,
                      qreal theta2,
                      const QColor& color) {
    ScopedDrawGuard guard(this, GL_QUAD_STRIP);
    if (innerRadius <= 0) {
      qWarning() << "inner radius must be positive.";
      return;
    }
    if (outterRadius <= 0) {
      qWarning() << "outter radius must be positive.";
      return;
    }
    if (innerRadius >= outterRadius) {
      qWarning() << "inner radius must be less than outter radius.";
      return;
    }
    putColor(color);
    qreal dTheta = 1.0 / outterRadius;
    for (qreal theta = theta1; theta < theta2 + dTheta; theta += dTheta) {
      qreal cos = std::cos(theta), sin = std::sin(theta);
      putVertices(origin + outterRadius * Vertex(cos, sin),
                  origin + innerRadius * Vertex(cos, sin));
    }
  }

  inline void drawArc(const Vertex& origin,
                      qreal innerRadius,
                      qreal outterRadius,
                      const QColor& color) {
    drawArc(origin, innerRadius, outterRadius, 0, 2 * PI, color);
  }

  inline void drawSector(const Vertex& origin,
                         qreal radius,
                         qreal theta1,
                         qreal theta2,
                         const QColor& color) {
    ScopedDrawGuard guard(this, GL_TRIANGLE_FAN);
    if (radius <= 0) {
      qWarning() << "radius must be positive.";
      return;
    }
    putColor(color);
    putVertex(origin);
    qreal dTheta = 1.0 / radius;
    for (qreal theta = theta1; theta < theta2 + dTheta; theta += dTheta) {
      putVertex(origin + radius * Vertex(std::cos(theta), std::sin(theta)));
    }
  }

  inline void drawCircleSegment(const Vertex& origin,
                                qreal radius,
                                qreal theta1,
                                qreal theta2,
                                const QColor& color) {
    ScopedDrawGuard guard(this, GL_POLYGON);
    if (radius <= 0) {
      qWarning() << "radius must be positive.";
      return;
    }
    putColor(color);
    qreal dTheta = 1.0 / radius;
    for (qreal theta = theta1; theta < theta2 + dTheta; theta += dTheta) {
      putVertex(origin + radius * Vertex(std::cos(theta), std::sin(theta)));
    }
  }

  inline void
  drawFilledCircle(const Vertex& origin, qreal radius, const QColor& color) {
    if (!local.circleDisplayListId) {
      DisplayListGuard displayGuard(this);
      ScopedDrawGuard guard(this, GL_POLYGON, true);
      qreal dTheta = 1.0 / 1000.0;
      for (qreal theta = 0; theta < 2 * PI + dTheta; theta += dTheta) {
        putVertex(Vertex(std::cos(theta), std::sin(theta)));
      }
      local.circleDisplayListId = displayGuard.key();
    }
    glMatrixMode(GL_MODELVIEW);
    PushPopGuard pushPopGuard(this);
    putColor(color);
    translateZ();
    translateXYScaleAndRotate(origin, radius, 0);
    return callListAndIncrementZ(*local.circleDisplayListId);
  }
};

#endif // GAMEVISUALIZERPAINTER2D_H
