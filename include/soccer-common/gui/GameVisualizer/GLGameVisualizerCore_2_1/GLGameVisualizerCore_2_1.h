#ifndef GLGAMEVISUALIZERCORE_2_1_H
#define GLGAMEVISUALIZERCORE_2_1_H

#include <QColor>
#include <QPointF>
#include <QPolygonF>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLFunctions_2_1>

#if __has_include(<GL/glu.h>)
  #include <GL/glu.h>
#else
  #error open gl not found.
#endif

class GLGameVisualizerCore_2_1 : public QOpenGLFunctions_2_1 {
 protected:
  qreal m_z;

  struct Const {
    static constexpr qreal zStep = 0.1;
  };

 public:
  struct Vertex : public QPointF {
    constexpr Vertex() : QPointF() {
    }
    constexpr Vertex(qreal x, qreal y) : QPointF(x, y) {
    }
    constexpr Vertex(const QPoint& p) : QPointF(p) {
    }
    constexpr Vertex(const QPointF& p) : QPointF(p) {
    }
    constexpr Vertex(const QVector2D& v) : QPointF(v.x(), v.y()) {
    }
    constexpr Vertex(const QVector3D& v) : QPointF(v.x(), v.y()) {
    }
    template <class U, class V>
    constexpr Vertex(const QPair<U, V>& p) : QPointF(p.first, p.second) {
    }
    template <class U, class V>
    constexpr Vertex(const std::pair<U, V>& p) : QPointF(p.first, p.second) {
    }

    friend constexpr bool operator==(const Vertex& lhs, const Vertex& rhs) {
      return qFuzzyCompare(lhs.x(), rhs.x()) && qFuzzyCompare(lhs.y(), rhs.y());
    }
  };

  struct Polygon : public QVector<Vertex> {
    inline Polygon() : QVector<Vertex>() {
    }
    inline Polygon(const QVector<Vertex>& polygon) : QVector<Vertex>(polygon) {
    }
    inline Polygon(const QVector<QPoint>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QPointF>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QVector2D>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QVector3D>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class U, class V>
    inline Polygon(const QVector<QPair<U, V>>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class U, class V>
    inline Polygon(const QVector<std::pair<U, V>>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class U>
    inline Polygon(const std::initializer_list<U>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }

    inline operator QPolygonF() const {
      QPolygonF ret;
      ret.reserve(size());
      for (auto vertex : *this) {
        ret += vertex;
      }
      return ret;
    }
  };

  class PushPopGuard {
    GLGameVisualizerCore_2_1* f;

   public:
    Q_DISABLE_COPY_MOVE(PushPopGuard);

    inline PushPopGuard(GLGameVisualizerCore_2_1* t_f) : f(t_f) {
      Q_ASSERT(f != nullptr);
      f->glPushMatrix();
      f->glLoadIdentity();
    }
    inline ~PushPopGuard() {
      f->glPopMatrix();
    }
  };

  class ScopedDrawGuard {
    GLGameVisualizerCore_2_1* f;
    bool isDisplayListCall;
    qreal z;

   public:
    Q_DISABLE_COPY_MOVE(ScopedDrawGuard);

    inline ScopedDrawGuard(GLGameVisualizerCore_2_1* t_f,
                           GLenum mode,
                           bool t_isDisplayListCall = false) :
        f(t_f),
        isDisplayListCall(t_isDisplayListCall),
        z(f->m_z) {
      Q_ASSERT(f != nullptr);
      f->glBegin(mode);
      if (isDisplayListCall) {
        f->setZ(0);
      }
    }
    inline ~ScopedDrawGuard() {
      f->glEnd();
      if (isDisplayListCall) {
        f->setZ(z);
      } else {
        f->m_z += Const::zStep;
      }
    }
  };

  class DisplayListGuard {
    QOpenGLFunctions_2_1* f;
    GLuint m_key;

   public:
    Q_DISABLE_COPY_MOVE(DisplayListGuard);

    inline DisplayListGuard(QOpenGLFunctions_2_1* t_f) :
        f(t_f),
        m_key(f->glGenLists(1)) {
      Q_ASSERT(f != nullptr);
      f->glNewList(m_key, GL_COMPILE);
    }

    inline ~DisplayListGuard() {
      f->glEndList();
    }

    inline GLuint key() const {
      return m_key;
    }
  };

  void callListAndIncrementZ(GLuint id);

  void putVertex(const Vertex& v);

  template <class... Args>
  void putVertices(const Args&... args) {
    (putVertex(args), ...);
  }

  void putBackgroundColor(const QColor& color);
  void putColor(const QColor& color);

  void translateZ();
  void translateXY(qreal x, qreal y);
  void translateXYScaleAndRotate(const Vertex& pos, qreal size, qreal angle);

  void setZ(qreal z);

  GLGameVisualizerCore_2_1();
  ~GLGameVisualizerCore_2_1();
};

#endif // GLGAMEVISUALIZERCORE_2_1_H
