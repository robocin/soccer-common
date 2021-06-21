#ifndef SOCCER_COMMON_BALL_H
#define SOCCER_COMMON_BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  class RawBall : virtual public RawEntity {
   protected:
   public:
    explicit RawBall(const RawEntity& rawEntity);
    explicit RawBall(const QPointF& position);

    using RawEntity::position;
    using RawEntity::operator const QPointF&;

    bool operator<(const RawBall& other) const;
    bool operator==(const RawBall& other) const;
    bool operator!=(const RawBall& other) const;
  };

  // ------------------------------------------------------------------------ //

  class Ball : public Entity, public RawBall {
   protected:
   public:
    explicit Ball(const Entity& entity);
    Ball(const QPointF& position, const QPointF& velocity, const QPointF& acceleration);
    Ball(const RawBall& rawBall, const QPointF& velocity, const QPointF& acceleration);

    using Entity::position;
    using Entity::operator const QPointF&;
    using Entity::velocity;
    using Entity::acceleration;

    bool operator<(const Ball& other) const;
    bool operator==(const Ball& other) const;
    bool operator!=(const Ball& other) const;
  };
} // namespace Common

#endif // SOCCER_COMMON_BALL_H
