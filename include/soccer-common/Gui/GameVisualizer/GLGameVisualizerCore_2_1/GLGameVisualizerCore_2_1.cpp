#include "GLGameVisualizerCore_2_1.h"

void GLGameVisualizerCore_2_1::callListAndIncrementZ(GLuint id) {
  glCallList(id);
  m_z += Const::zStep;
}

void GLGameVisualizerCore_2_1::putBackgroundColor(const QColor& color) {
  GLfloat r, g, b, a;
  color.getRgbF(&r, &g, &b, &a);
  glClearColor(static_cast<GLfloat>(r),
               static_cast<GLfloat>(g),
               static_cast<GLfloat>(b),
               static_cast<GLfloat>(a));
}

void GLGameVisualizerCore_2_1::putColor(const QColor& color) {
  GLfloat r, g, b, a;
  color.getRgbF(&r, &g, &b, &a);
  glColor<qreal>(r, g, b, a);
}

void GLGameVisualizerCore_2_1::translateZ() {
  glTranslate<qreal>(0.0, 0.0, m_z);
}

void GLGameVisualizerCore_2_1::translateXY(qreal x, qreal y) {
  glTranslate<qreal>(x, y, 0.0);
}

void GLGameVisualizerCore_2_1::translateXYScaleAndRotate(const Vertex& pos,
                                                         qreal size,
                                                         qreal angle) {
  translateXYScaleAndRotateT<qreal>(pos, size, angle);
}

void GLGameVisualizerCore_2_1::setZ(qreal z) {
  m_z = z;
}

GLGameVisualizerCore_2_1::GLGameVisualizerCore_2_1() : m_z(0) {
}
