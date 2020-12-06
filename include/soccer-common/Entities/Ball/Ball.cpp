#include "Ball.h"

RawBall::RawBall(const QPointF& position) : RawEntity(position) {
}

Ball::Ball(const QPointF& position,
           const QPointF& velocity,
           const QPointF& acceleration) :
    RawEntity(position),
    Entity(position, velocity, acceleration),
    RawBall(position) {
}
