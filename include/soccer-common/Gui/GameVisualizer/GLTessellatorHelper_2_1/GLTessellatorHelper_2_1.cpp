#include "GLTessellatorHelper_2_1.h"
#include <QDebug>

void GLTessellatorHelper_2_1::tessBeginCB(GLenum which) {
  ::glBegin(which);
}

void GLTessellatorHelper_2_1::tessEndCB() {
  ::glEnd();
}

void GLTessellatorHelper_2_1::tessVertexCB(const GLvoid* data) {
  const auto* ptr = (const GLdouble*) data;
  ::glVertex3dv(ptr);
}

void GLTessellatorHelper_2_1::tessErrorCB(GLenum errorCode) {
  const GLubyte* errorStr;
  errorStr = ::gluErrorString(errorCode);
  qWarning() << "tessErrorCB" << (errorStr);
}

std::array<GLdouble, 3> GLTessellatorHelper_2_1::makeTessVertex(qreal x, qreal y) {
  return {x, y, m_z};
}

std::array<GLdouble, 3> GLTessellatorHelper_2_1::makeTessVertex(const Vertex& v) {
  return makeTessVertex(v.x(), v.y());
}
