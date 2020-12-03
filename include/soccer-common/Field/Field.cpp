#include "Field.h"

Field::Field(qreal fieldLength,
             qreal fieldWidth,
             qreal goalWidth,
             qreal goalDepth) :
    m_fieldLength(fieldLength),
    m_fieldWidth(fieldWidth),
    m_goalWidth(goalWidth),
    m_goalDepth(goalDepth) {
}

qreal Field::fieldLength() const {
  return m_fieldLength;
}

qreal Field::fieldWidth() const {
  return m_fieldWidth;
}

qreal Field::goalWidth() const {
  return m_goalWidth;
}

qreal Field::goalDepth() const {
  return m_goalDepth;
}
