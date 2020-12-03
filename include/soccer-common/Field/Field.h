#ifndef FIELD_H
#define FIELD_H

#include <QtCore>

class Field {
 private:
  qreal m_fieldLength;
  qreal m_fieldWidth;

  qreal m_goalWidth;
  qreal m_goalDepth;

 public:
  Field(qreal fieldLength, qreal fieldWidth, qreal goalWidth, qreal goalDepth);

  qreal fieldLength() const;
  qreal fieldWidth() const;
  qreal goalWidth() const;
  qreal goalDepth() const;
};

#endif // FIELD_H
