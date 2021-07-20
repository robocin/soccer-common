#ifndef SOCCER_COMMON_BALL_H
#define SOCCER_COMMON_BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  template <class PT>
  class RawBall : virtual public RawEntity<PT> {
   protected:
   public:
    constexpr explicit RawBall(const RawEntity<PT>& rawEntity) : RawEntity<PT>(rawEntity) {
    }

    constexpr explicit RawBall(const PT& position) : RawBall(RawEntity(position)) {
    }

    using RawEntity<PT>::position;
    using RawEntity<PT>::operator const PT&;

    using RawEntity<PT>::distSquaredTo;
    using RawEntity<PT>::distTo;

    constexpr bool operator<(const RawBall& other) const {
      return static_cast<const RawEntity<PT>&>(*this) < static_cast<const RawEntity<PT>&>(other);
    }
    constexpr bool operator==(const RawBall& other) const {
      return static_cast<const RawEntity<PT>&>(*this) == static_cast<const RawEntity<PT>&>(other);
    }
    constexpr bool operator!=(const RawBall& other) const {
      return !(other == *this);
    }
  };

  // -------------------------------------------------------------------------------------------- //

  template <class PT>
  class Ball : public Entity<PT>, public RawBall<PT> {
   protected:
   public:
    constexpr explicit Ball(const Entity<PT>& entity) :
        RawEntity<PT>(entity.position()),
        RawBall<PT>(entity.position()),
        Entity<PT>(entity) {
    }

    constexpr Ball(const RawBall<PT>& rawBall, const PT& velocity, const PT& acceleration) :
        Ball(Entity(rawBall.position(), velocity, acceleration)) {
    }

    constexpr Ball(const PT& position, const PT& velocity, const PT& acceleration) :
        Ball(Entity(position, velocity, acceleration)) {
    }

    using Entity<PT>::position;
    using Entity<PT>::operator const PT&;
    using Entity<PT>::velocity;
    using Entity<PT>::acceleration;

    using RawEntity<PT>::distSquaredTo;
    using RawEntity<PT>::distTo;

    constexpr bool operator<(const Ball& other) const {
      return static_cast<const Entity<PT>&>(*this) < static_cast<const Entity<PT>&>(other);
    }
    constexpr bool operator==(const Ball& other) const {
      return static_cast<const Entity<PT>&>(*this) == static_cast<const Entity<PT>&>(other);
    }
    constexpr bool operator!=(const Ball& other) const {
      return !(other == *this);
    }
  };
} // namespace Common

#ifndef QT_NO_DEBUG_STREAM
template <class PT>
QDebug operator<<(QDebug dbg, const Common::RawBall<PT>& ball) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << Qt::fixed << qSetRealNumberPrecision(2);
  dbg << "Ball(position(" << ball.position().x() << ',' << ball.position().y() << "))";
  return dbg;
}
#endif

#endif // SOCCER_COMMON_BALL_H
