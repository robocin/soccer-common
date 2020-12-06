#ifndef BALL_H
#define BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

class RawBall : virtual public RawEntity {
 public:
  RawBall(const QPointF& position);
};

class Ball : public Entity, public RawBall {
 public:
  Ball(const QPointF& position,
       const QPointF& velocity,
       const QPointF& acceleration);
};

#endif // BALL_H
