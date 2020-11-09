#include "Robot.h"

RawRobot::RawRobot(int _id, qreal _angle, const QPointF& _position) :
    RawEntity(_position),
    m_id(_id),
    m_angle(_angle) {
}

int RawRobot::id() const {
  return m_id;
}

qreal RawRobot::angle() const {
  return m_angle;
}

Robot::Robot(int _id,
             qreal _angle,
             const QPointF& _position,
             const QPointF& _velocity,
             const QPointF& _acceleration) :
    RawEntity(_position),
    Entity(_position, _velocity, _acceleration),
    RawRobot(_id, _angle, _position) {
}
