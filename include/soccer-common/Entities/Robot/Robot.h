#ifndef ROBOT_H
#define ROBOT_H

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
 public:
  Robot(int id,
        qreal angle,
        const QPointF& position,
        const QPointF& velocity,
        const QPointF& acceleration);
};

#endif // ROBOT_H
