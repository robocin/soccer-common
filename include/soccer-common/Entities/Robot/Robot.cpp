#include "Robot.h"
#include "soccer-common/Geometry/Geometry.h"

using Geometry2D::operator<;

namespace Common {
  RawRobot::RawRobot(int id, qreal angle, const RawEntity& rawEntity) :
      RawEntity(rawEntity),
      m_id(id),
      m_angle(angle) {
  }

  RawRobot::RawRobot(int id, qreal angle, const QPointF& position) :
      RawRobot(id, angle, RawEntity(position)) {
  }

  int RawRobot::id() const {
    return m_id;
  }

  qreal RawRobot::angle() const {
    return m_angle;
  }

  bool RawRobot::operator<(const RawRobot& other) const {
    return std::tie(m_id, m_angle, static_cast<const RawEntity&>(*this)) <
           std::tie(other.m_id, other.m_angle, static_cast<const RawEntity&>(other));
  }

  bool RawRobot::operator==(const RawRobot& other) const {
    return std::tie(m_id, m_angle, static_cast<const RawEntity&>(*this)) ==
           std::tie(other.m_id, other.m_angle, static_cast<const RawEntity&>(other));
  }

  bool RawRobot::operator!=(const RawRobot& other) const {
    return !(other == *this);
  }

  // ------------------------------------------------------------------------ //

  Robot::Robot(int id, qreal angle, const Entity& entity) :
      RawEntity(entity.position()),
      Entity(entity),
      RawRobot(id, angle, entity.position()) {
  }

  Robot::Robot(const RawRobot& rawRobot, const QPointF& velocity, const QPointF& acceleration) :
      Robot(rawRobot.id(), rawRobot.angle(), Entity(rawRobot.position(), velocity, acceleration)) {
  }

  Robot::Robot(int id,
               qreal angle,
               const QPointF& position,
               const QPointF& velocity,
               const QPointF& acceleration) :
      Robot(id, angle, Entity(position, velocity, acceleration)) {
  }

  bool Robot::operator<(const Robot& other) const {
    return std::tie(m_id, m_angle, static_cast<const Entity&>(*this)) <
           std::tie(other.m_id, other.m_angle, static_cast<const Entity&>(other));
  }

  bool Robot::operator==(const Robot& other) const {
    return std::tie(m_id, m_angle, static_cast<const Entity&>(*this)) ==
           std::tie(other.m_id, other.m_angle, static_cast<const Entity&>(other));
  }

  bool Robot::operator!=(const Robot& other) const {
    return !(other == *this);
  }
} // namespace Common