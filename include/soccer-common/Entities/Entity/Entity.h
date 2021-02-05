#ifndef SOCCER_COMMON_ENTITY_H
#define SOCCER_COMMON_ENTITY_H

#include <QPointF>

class RawEntity {
  QPointF m_position;

 public:
  explicit RawEntity(const QPointF& position);

  const QPointF& position() const;
  operator const QPointF&() const;
};

class Entity : virtual public RawEntity {
  QPointF m_velocity;
  QPointF m_acceleration;

 public:
  Entity(const QPointF& position,
         const QPointF& velocity,
         const QPointF& acceleration);

  const QPointF& velocity() const;
  const QPointF& acceleration() const;
};

#endif // SOCCER_COMMON_ENTITY_H
