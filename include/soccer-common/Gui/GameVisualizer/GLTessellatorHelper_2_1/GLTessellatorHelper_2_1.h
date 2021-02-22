#ifndef SOCCER_COMMON_GLTESSELLATORHELPER_2_1_H
#define SOCCER_COMMON_GLTESSELLATORHELPER_2_1_H

#include "soccer-common/Gui/GameVisualizer/GLGameVisualizerCore_2_1/GLGameVisualizerCore_2_1.h"

class GLTessellatorHelper_2_1 : public GLGameVisualizerCore_2_1 {
  static void tessBeginCB(GLenum which);
  static void tessEndCB();
  static void tessVertexCB(const GLvoid* data);
  static void tessErrorCB(GLenum errorCode);

 public:
  class TessScopedDrawGuard {
    GLTessellatorHelper_2_1* f;
    GLUtesselator* m_tess;
    bool isDisplayListCall;
    qreal z;

   public:
    Q_DISABLE_COPY_MOVE(TessScopedDrawGuard);

    inline explicit TessScopedDrawGuard(GLTessellatorHelper_2_1* t_f,
                                        bool t_isDisplayListCall = false) :
        f(t_f),
        m_tess(gluNewTess()),
        isDisplayListCall(t_isDisplayListCall),
        z(f->m_z) {
      Q_ASSERT(f != nullptr);
      gluTessCallback(m_tess, GLU_TESS_BEGIN, (_GLUfuncptr) tessBeginCB);
      gluTessCallback(m_tess, GLU_TESS_END, (_GLUfuncptr) tessEndCB);
      gluTessCallback(m_tess, GLU_TESS_ERROR, (_GLUfuncptr) tessErrorCB);
      gluTessCallback(m_tess, GLU_TESS_VERTEX, (_GLUfuncptr) tessVertexCB);
      // gluTessCallback(tess, GLU_TESS_COMBINE, (_GLUfuncptr) tessCombineCB);

      f->glMatrixMode(GL_MODELVIEW);
      f->glPushMatrix();
      f->glLoadIdentity();

      if (isDisplayListCall) {
        f->setZ(0);
      }
    }
    inline ~TessScopedDrawGuard() {
      f->glPopMatrix();
      gluDeleteTess(m_tess);
      if (isDisplayListCall) {
        f->setZ(z);
      } else {
        f->m_z += Const::zStep;
      }
    }

    inline GLUtesselator* tess() {
      return m_tess;
    }
  };

  class TessContourGuard {
    GLUtesselator* tess;

   public:
    Q_DISABLE_COPY_MOVE(TessContourGuard);

    inline explicit TessContourGuard(GLUtesselator* t_tess) : tess(t_tess) {
      Q_ASSERT(tess != nullptr);
      gluTessBeginContour(tess);
    }
    inline ~TessContourGuard() {
      gluTessEndContour(tess);
    }
  };

  class TessPolygonGuard {
    GLUtesselator* tess;

   public:
    Q_DISABLE_COPY_MOVE(TessPolygonGuard);

    inline explicit TessPolygonGuard(GLUtesselator* t_tess) : tess(t_tess) {
      Q_ASSERT(tess != nullptr);
      gluTessBeginPolygon(tess, nullptr);
    }
    inline ~TessPolygonGuard() {
      gluTessEndPolygon(tess);
    }
  };

  std::array<GLdouble, 3> makeTessVertex(qreal x, qreal y);
  std::array<GLdouble, 3> makeTessVertex(const Vertex& v);

  GLTessellatorHelper_2_1() = default;
  ~GLTessellatorHelper_2_1() override = default;
};

#endif // SOCCER_COMMON_GLTESSELLATORHELPER_2_1_H
