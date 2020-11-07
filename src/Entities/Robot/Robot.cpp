#include "Robot.h"

RawRobot::RawRobot(int _id, const QPointF& _position) :
    RawEntity(_position),
    m_id(_id) {
}

int RawRobot::id() const {
  return m_id;
}

Robot::Robot(int _id,
             const QPointF& _position,
             const QPointF& _velocity,
             const QPointF& _acceleration) :
    RawEntity(_position),
    Entity(_position, _velocity, _acceleration),
    RawRobot(_id, _position) {
}
