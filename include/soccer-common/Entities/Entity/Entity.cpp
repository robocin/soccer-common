#include "Entity.h"
#include "soccer-common/Geometry/Geometry.h"

using Geometry2D::operator<;

namespace Common {
  RawEntity::RawEntity(const QPointF& position) : m_position(position) {
  }

  const QPointF& RawEntity::position() const {
    return m_position;
  }

  RawEntity::operator const QPointF&() const {
    return position();
  }

  bool RawEntity::operator<(const RawEntity& other) const {
    return m_position < other.m_position;
  }

  bool RawEntity::operator==(const RawEntity& other) const {
    return m_position == other.m_position;
  }

  bool RawEntity::operator!=(const RawEntity& other) const {
    return !(other == *this);
  }

  // ------------------------------------------------------------------------ //

  Entity::Entity(const RawEntity& rawEntity, const QPointF& velocity, const QPointF& acceleration) :
      RawEntity(rawEntity),
      m_velocity(velocity),
      m_acceleration(acceleration) {
  }

  Entity::Entity(const QPointF& position, const QPointF& velocity, const QPointF& acceleration) :
      Entity(RawEntity(position), velocity, acceleration) {
  }

  const QPointF& Entity::velocity() const {
    return m_velocity;
  }

  const QPointF& Entity::acceleration() const {
    return m_acceleration;
  }

  bool Entity::operator<(const Entity& other) const {
    return std::tie(m_position, m_velocity, m_acceleration) <
           std::tie(other.m_position, other.m_velocity, other.m_acceleration);
  }

  bool Entity::operator==(const Entity& other) const {
    return std::tie(m_position, m_velocity, m_acceleration) ==
           std::tie(other.m_position, other.m_velocity, other.m_acceleration);
  }

  bool Entity::operator!=(const Entity& other) const {
    return !(other == *this);
  }
} // namespace Common