#include "Entity.h"

RawEntity::RawEntity(const QPointF& position) : m_position(position) {
}

const QPointF& RawEntity::position() const {
  return m_position;
}

RawEntity::operator const QPointF&() const {
  return position();
}

Entity::Entity(const QPointF& position,
               const QPointF& velocity,
               const QPointF& acceleration) :
    RawEntity(position),
    m_velocity(velocity),
    m_acceleration(acceleration) {
}

const QPointF& Entity::velocity() const {
  return m_velocity;
}

const QPointF& Entity::acceleration() const {
  return m_acceleration;
}
