#ifndef ROBOT_H
#define ROBOT_H

#include "Entities/Entity/Entity.h"

class RawRobot : virtual public RawEntity {
  int m_id;

 public:
  RawRobot(int _id, const QPointF& _position);

  int id() const;
};

class Robot : public Entity, public RawRobot {
 public:
  Robot(int _id,
        const QPointF& _position,
        const QPointF& _velocity,
        const QPointF& _acceleration);
};

#endif // ROBOT_H
