#ifndef SOCCER_COMMON_ENTITY_H
#define SOCCER_COMMON_ENTITY_H

#include <tuple>

namespace Common {
  template <class PT>
  class RawEntity {
   protected:
    PT m_position;

    RawEntity() = default;

   public:
    constexpr explicit RawEntity(const PT& position) : m_position(position) {
    }

    constexpr const PT& position() const {
      return m_position;
    }
    constexpr operator const PT&() const { // NOLINT(google-explicit-constructor)
      return position();
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

#endif // SOCCER_COMMON_ENTITY_H
