#ifndef SOCCER_COMMON_FIELD_H
#define SOCCER_COMMON_FIELD_H

#include <QtCore>

class Field {
 private:
  qreal m_length;
  qreal m_width;

  qreal m_goalWidth;
  qreal m_goalDepth;

 public:
  Field(qreal length, qreal width, qreal goalWidth, qreal goalDepth);

  qreal length() const;
  qreal width() const;
  qreal goalWidth() const;
  qreal goalDepth() const;
};

#endif // SOCCER_COMMON_FIELD_H
