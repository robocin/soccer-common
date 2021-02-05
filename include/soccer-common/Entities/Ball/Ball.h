#ifndef SOCCER_COMMON_BALL_H
#define SOCCER_COMMON_BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

class RawBall : virtual public RawEntity {
 public:
  explicit RawBall(const QPointF& position);
};

class Ball : public Entity, public RawBall {
 public:
  Ball(const QPointF& position,
       const QPointF& velocity,
       const QPointF& acceleration);
};

#endif // SOCCER_COMMON_BALL_H
