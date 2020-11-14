#ifndef ROBOT_H
#define ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

class RawRobot : virtual public RawEntity {
  int m_id;
  qreal m_angle;

 public:
  RawRobot(int _id, qreal _angle, const QPointF& _position);

  int id() const;
  qreal angle() const;
};

class Robot : public Entity, public RawRobot {
 public:
  Robot(int _id,
        qreal _angle,
        const QPointF& _position,
        const QPointF& _velocity,
        const QPointF& _acceleration);
};

#endif // ROBOT_H
