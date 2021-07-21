#ifndef SOCCER_COMMON_ENTITY_H
#define SOCCER_COMMON_ENTITY_H

#include <tuple>
#include <QDebug>
#include "soccer-common/Geometry/Geometry.h"

namespace Common {
  template <class PT>
  class RawEntity {
   protected:
    PT m_position;

   public:
    constexpr explicit RawEntity(const PT& position) : m_position(position) {
    }

    constexpr const PT& position() const {
      return m_position;
    }
    constexpr operator const PT&() const { // NOLINT(google-explicit-constructor)
      return position();
    }

    constexpr auto distSquaredTo(const PT& other) const {
      return Geometry2D::distanceSquared<PT>(m_position, other);
    }

    constexpr auto distTo(const PT& other) const {
      return Geometry2D::distance<PT>(m_position, other);
    }

    constexpr bool operator<(const RawEntity& other) const {
      return m_position < other.m_position;
    }
    constexpr bool operator==(const RawEntity& other) const {
      return m_position == other.m_position;
    }
    constexpr bool operator!=(const RawEntity& other) const {
      return !(other == *this);
    }
  };

  // -------------------------------------------------------------------------------------------- //

  template <class PT>
  class Entity : virtual public RawEntity<PT> {
   protected:
    using RawEntity<PT>::m_position;
    PT m_velocity;
    PT m_acceleration;

   public:
    constexpr Entity(const RawEntity<PT>& rawEntity, const PT& velocity, const PT& acceleration) :
        RawEntity<PT>(rawEntity),
        m_velocity(velocity),
        m_acceleration(acceleration) {
    }
    constexpr Entity(const PT& position, const PT& velocity, const PT& acceleration) :
        Entity(RawEntity(position), velocity, acceleration) {
    }

    using RawEntity<PT>::position;
    using RawEntity<PT>::operator const PT&;

    constexpr const PT& velocity() const {
      return m_velocity;
    }
    constexpr const PT& acceleration() const {
      return m_acceleration;
    }

    using RawEntity<PT>::distSquaredTo;
    using RawEntity<PT>::distTo;

    constexpr bool operator<(const Entity& other) const {
      return std::tie(m_position, m_velocity, m_acceleration) <
             std::tie(other.m_position, other.m_velocity, other.m_acceleration);
    }
    constexpr bool operator==(const Entity& other) const {
      return std::tie(m_position, m_velocity, m_acceleration) ==
             std::tie(other.m_position, other.m_velocity, other.m_acceleration);
    }
    constexpr bool operator!=(const Entity& other) const {
      return !(other == *this);
    }
  };
} // namespace Common

#ifndef QT_NO_DEBUG_STREAM
template <class PT>
QDebug operator<<(QDebug dbg, const Common::RawEntity<PT>& entity) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << Qt::fixed << qSetRealNumberPrecision(2);
  dbg << "Entity(position(" << entity.position().x() << ',' << entity.position().y() << "))";
  return dbg;
}
#endif

#endif // SOCCER_COMMON_ENTITY_H
