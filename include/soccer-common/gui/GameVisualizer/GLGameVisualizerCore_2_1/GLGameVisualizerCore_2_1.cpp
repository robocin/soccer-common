#include "GLGameVisualizerCore_2_1.h"

void GLGameVisualizerCore_2_1::callListAndIncrementZ(GLuint id) {
  glCallList(id);
  m_z += Const::zStep;
}

void GLGameVisualizerCore_2_1::putVertex(const Vertex& v) {
  if constexpr (std::is_same_v<qreal, GLfloat>) {
    glVertex3f(v.x(), v.y(), m_z);
  } else if constexpr (std::is_same_v<qreal, GLdouble>) {
    glVertex3d(v.x(), v.y(), m_z);
  }
}

void GLGameVisualizerCore_2_1::putBackgroundColor(const QColor& color) {
  qreal r, g, b, a;
  color.getRgbF(&r, &g, &b, &a);
  glClearColor(r, g, b, a);
}

void GLGameVisualizerCore_2_1::putColor(const QColor& color) {
  qreal r, g, b, a;
  color.getRgbF(&r, &g, &b, &a);
  if constexpr (std::is_same_v<qreal, GLfloat>) {
    glColor4f(r, g, b, a);
  } else if constexpr (std::is_same_v<qreal, GLdouble>) {
    glColor4d(r, g, b, a);
  }
}

void GLGameVisualizerCore_2_1::translateZ() {
  if constexpr (std::is_same_v<qreal, GLfloat>) {
    glTranslatef(0.0f, 0.0f, m_z);
  } else if constexpr (std::is_same_v<qreal, GLdouble>) {
    glTranslated(0.0, 0.0, m_z);
  }
}

void GLGameVisualizerCore_2_1::translateXY(qreal x, qreal y) {
  if constexpr (std::is_same_v<qreal, GLfloat>) {
    glTranslatef(x, y, 0.0f);
  } else if constexpr (std::is_same_v<qreal, GLdouble>) {
    glTranslated(x, y, 0.0);
  }
}

void GLGameVisualizerCore_2_1::translateXYScaleAndRotate(const Vertex& pos,
                                                         qreal size,
                                                         qreal angle) {
  if constexpr (std::is_same_v<qreal, GLfloat>) {
    glTranslatef(pos.x(), pos.y(), 0.0f);
    glScalef(size, size, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
  } else if constexpr (std::is_same_v<qreal, GLdouble>) {
    glTranslated(pos.x(), pos.y(), 0.0);
    glScaled(size, size, 1.0);
    glRotated(angle, 0.0, 0.0, 1.0);
  }
}

void GLGameVisualizerCore_2_1::setZ(qreal z) {
  m_z = z;
}

GLGameVisualizerCore_2_1::GLGameVisualizerCore_2_1() : m_z(0) {
}

GLGameVisualizerCore_2_1::~GLGameVisualizerCore_2_1() {
}
