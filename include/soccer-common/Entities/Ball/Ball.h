#ifndef SOCCER_COMMON_BALL_H
#define SOCCER_COMMON_BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  /*!
   * @brief Ball class that holds only telemetry data
   * 
   */
  template <class PT>
  class RawBall : virtual public RawEntity<PT> {
   protected:
   public:
    /*!
     * @brief Class constructor
     * 
     * @param rawEntity - rawEntity instance 
     */
    constexpr explicit RawBall(const RawEntity<PT>& rawEntity) : RawEntity<PT>(rawEntity) {
    }

    /*!
     * @brief Class constructor
     * 
     * @param position - Current ball position 
     */
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

  /*!
   * @brief Ball class that holds telemetry data plus calculated values. 
   * 
   */
  template <class PT>
  class Ball : public RawBall<PT>, public Entity<PT> {
   protected:
   public:
    /*!
     * @brief Class constructor
     * 
     * @param entity - entity instance 
     */
    constexpr explicit Ball(const Entity<PT>& entity) :
        Entity<PT>(entity),
        RawBall<PT>(entity.position()),
        RawEntity<PT>(entity.position()) {
    }
    /*!
     * @brief Class constructor
     * 
     * @param rawBall - RawBall instance 
     * @param velocity - Current velocity 
     * @param acceleration - Current acceleration 
     */
    constexpr Ball(const RawBall<PT>& rawBall, const PT& velocity, const PT& acceleration) :
        Ball(Entity(rawBall.position(), velocity, acceleration)) {
    }
    /*!
     * @brief Class constructor
     * 
     * @param position - Current position 
     * @param velocity - Current velocity 
     * @param acceleration - Current acceleration 
     */
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
