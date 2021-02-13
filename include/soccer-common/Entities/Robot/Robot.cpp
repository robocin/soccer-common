#include "Robot.h"

RawRobot::RawRobot(int id, qreal angle, const QPointF& position) :
    RawEntity(position),
    m_id(id),
    m_angle(angle) {
}

int RawRobot::id() const {
  return m_id;
}

qreal RawRobot::angle() const {
  return m_angle;
}

Robot::Robot(int id,
             qreal angle,
             const QPointF& position,
             const QPointF& velocity,
             const QPointF& acceleration,
             qreal angularVelocity) :
    RawEntity(position),
    Entity(position, velocity, acceleration),
    RawRobot(id, angle, position),
    m_angularVelocity(angularVelocity) {
}

qreal Robot::angularVelocity() const {
  return m_angularVelocity;
}
