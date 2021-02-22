#ifndef SOCCER_COMMON_ROBOT_H
#define SOCCER_COMMON_ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

class RawRobot : virtual public RawEntity {
  int m_id;
  qreal m_angle;

 public:
  RawRobot(int id, qreal angle, const QPointF& position);

  int id() const;
  qreal angle() const;
};

class Robot : public Entity, public RawRobot {
  qreal m_angularVelocity;

 public:
  Robot(int id,
        qreal angle,
        const QPointF& position,
        const QPointF& velocity,
        const QPointF& acceleration,
        qreal angularVelocity);

  qreal angularVelocity() const;
};

#endif // SOCCER_COMMON_ROBOT_H
