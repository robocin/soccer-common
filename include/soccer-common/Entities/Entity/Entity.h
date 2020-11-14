#ifndef ENTITY_H
#define ENTITY_H

#include <QPointF>

class RawEntity {
  QPointF m_position;

 public:
  RawEntity(const QPointF& _position);

  const QPointF& position() const;
};

class Entity : virtual public RawEntity {
  QPointF m_velocity;
  QPointF m_acceleration;

 public:
  Entity(const QPointF& _position,
         const QPointF& _velocity,
         const QPointF& _acceleration);

  const QPointF& velocity() const;
  const QPointF& acceleration() const;
};

#endif // ENTITY_H
