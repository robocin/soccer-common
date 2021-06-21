#include "Ball.h"
#include "soccer-common/Geometry/Geometry.h"

using Geometry2D::operator<;

namespace Common {
  RawBall::RawBall(const RawEntity& rawEntity) : RawEntity(rawEntity) {
  }

  RawBall::RawBall(const QPointF& position) : RawBall(RawEntity(position)) {
  }

  bool RawBall::operator<(const RawBall& other) const {
    return static_cast<const RawEntity&>(*this) < static_cast<const RawEntity&>(other);
  }

  bool RawBall::operator==(const RawBall& other) const {
    return static_cast<const RawEntity&>(*this) == static_cast<const RawEntity&>(other);
  }

  bool RawBall::operator!=(const RawBall& other) const {
    return !(other == *this);
  }

  // ------------------------------------------------------------------------ //

  Ball::Ball(const Entity& entity) :
      RawEntity(entity.position()),
      Entity(entity),
      RawBall(entity.position()) {
  }

  Ball::Ball(const RawBall& rawBall, const QPointF& velocity, const QPointF& acceleration) :
      Ball(Entity(rawBall.position(), velocity, acceleration)) {
  }

  Ball::Ball(const QPointF& position, const QPointF& velocity, const QPointF& acceleration) :
      Ball(Entity(position, velocity, acceleration)) {
  }

  bool Ball::operator<(const Ball& other) const {
    return static_cast<const Entity&>(*this) < static_cast<const Entity&>(other);
  }

  bool Ball::operator==(const Ball& other) const {
    return static_cast<const Entity&>(*this) == static_cast<const Entity&>(other);
  }

  bool Ball::operator!=(const Ball& other) const {
    return !(other == *this);
  }
} // namespace Common