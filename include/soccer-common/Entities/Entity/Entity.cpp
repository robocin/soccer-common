#include "Entity.h"

RawEntity::RawEntity(const QPointF& _position) : m_position(_position) {
}

const QPointF& RawEntity::position() const {
  return m_position;
}

Entity::Entity(const QPointF& _position,
               const QPointF& _velocity,
               const QPointF& _acceleration) :
    RawEntity(_position),
    m_velocity(_velocity),
    m_acceleration(_acceleration) {
}

const QPointF& Entity::velocity() const {
  return m_velocity;
}

const QPointF& Entity::acceleration() const {
  return m_acceleration;
}
