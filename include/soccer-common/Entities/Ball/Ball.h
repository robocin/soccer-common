#ifndef BALL_H
#define BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

class RawBall : virtual public RawEntity {
 public:
  RawBall(const QPointF& _position);
};

class Ball : public Entity, public RawBall {
 public:
  Ball(const QPointF& _position,
       const QPointF& _velocity,
       const QPointF& _acceleration);
};

#endif // BALL_H
