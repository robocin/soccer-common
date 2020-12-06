#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>

class RawEntity {
  QPointF m_position;

 public:
  RawEntity(const QPointF& position);

  QPointF position() const;
  operator QPointF() const;
};

class Entity : virtual public RawEntity {
  QPointF m_velocity;
  QPointF m_acceleration;

 public:
  Entity(const QPointF& position,
         const QPointF& velocity,
         const QPointF& acceleration);

  QPointF velocity() const;
  QPointF acceleration() const;
};

#endif // ENTITY_H
