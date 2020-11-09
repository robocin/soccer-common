#include "Ball.h"

RawBall::RawBall(const QPointF& _position) : RawEntity(_position) {
}

Ball::Ball(const QPointF& _position,
           const QPointF& _velocity,
           const QPointF& _acceleration) :
    RawEntity(_position),
    Entity(_position, _velocity, _acceleration),
    RawBall(_position) {
}
