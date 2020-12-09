#include "Field.h"

Field::Field(qreal length,
             qreal width,
             qreal goalWidth,
             qreal goalDepth) :
    m_length(length),
    m_width(width),
    m_goalWidth(goalWidth),
    m_goalDepth(goalDepth) {
}

qreal Field::length() const {
  return m_length;
}

qreal Field::width() const {
  return m_width;
}

qreal Field::goalWidth() const {
  return m_goalWidth;
}

qreal Field::goalDepth() const {
  return m_goalDepth;
}
