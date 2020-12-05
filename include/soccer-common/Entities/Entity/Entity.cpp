#include "Entity.h"

RawEntity::RawEntity(const QPointF& position) : m_position(position) {
}

QPointF RawEntity::position() const {
  return m_position;
}

Entity::Entity(const QPointF& position,
               const QPointF& velocity,
               const QPointF& acceleration) :
    RawEntity(position),
    m_velocity(velocity),
    m_acceleration(acceleration) {
}

QPointF Entity::velocity() const {
  return m_velocity;
}

QPointF Entity::acceleration() const {
  return m_acceleration;
}
