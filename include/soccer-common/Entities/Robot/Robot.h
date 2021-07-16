#ifndef SOCCER_COMMON_ROBOT_H
#define SOCCER_COMMON_ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  template <class PT>
  class RawRobot : virtual public RawEntity<PT> {
   protected:
    using RawEntity<PT>::m_position;
    int m_id{};
    float m_angle{};

   public:
    constexpr RawRobot(int id, float angle, const RawEntity<PT>& rawEntity) :
        RawEntity<PT>(rawEntity),
        m_id(id),
        m_angle(angle) {
    }
    constexpr RawRobot(int id, float angle, const PT& position) :
        RawRobot(id, angle, RawEntity(position)) {
    }

    using RawEntity<PT>::position;
    using RawEntity<PT>::operator const PT&;

    [[nodiscard]] constexpr int id() const {
      return m_id;
    }

    [[nodiscard]] constexpr float angle() const {
      return m_angle;
    }

    using RawEntity<PT>::distSquaredTo;
    using RawEntity<PT>::distTo;

    constexpr auto angleTo(const PT& p) const {
      return Geometry2D::angleBetween<PT>(Geometry2D::fromPolar<PT>(m_angle), p - m_position);
    }

    constexpr bool operator<(const RawRobot& other) const {
      return std::tie(m_id, m_angle, static_cast<const RawEntity<PT>&>(*this)) <
             std::tie(other.m_id, other.m_angle, static_cast<const RawEntity<PT>&>(other));
    }
    constexpr bool operator==(const RawRobot& other) const {
      return std::tie(m_id, m_angle, static_cast<const RawEntity<PT>&>(*this)) ==
             std::tie(other.m_id, other.m_angle, static_cast<const RawEntity<PT>&>(other));
    }
    constexpr bool operator!=(const RawRobot& other) const {
      return !(other == *this);
    }
  };

  // -------------------------------------------------------------------------------------------- //

  template <class PT>
  class Robot : public Entity<PT>, public RawRobot<PT> {
   protected:
    using RawRobot<PT>::m_id;
    using RawRobot<PT>::m_angle;

   public:
    constexpr Robot(int id, float angle, const Entity<PT>& entity) :
        RawEntity<PT>(entity.position()),
        Entity<PT>(entity),
        RawRobot<PT>(id, angle, entity.position()) {
    }
    constexpr Robot(const RawRobot<PT>& rawRobot, const PT& velocity, const PT& acceleration) :
        Robot(rawRobot.id(),
              rawRobot.angle(),
              Entity(rawRobot.position(), velocity, acceleration)) {
    }
    constexpr Robot(int id,
                    float angle,
                    const PT& position,
                    const PT& velocity,
                    const PT& acceleration) :
        Robot(id, angle, Entity(position, velocity, acceleration)) {
    }

    using RawRobot<PT>::id;
    using RawRobot<PT>::angle;

    using Entity<PT>::position;
    using Entity<PT>::operator const PT&;
    using Entity<PT>::velocity;
    using Entity<PT>::acceleration;

    using Entity<PT>::distSquaredTo;
    using Entity<PT>::distTo;
    using RawRobot<PT>::angleTo;

    constexpr bool operator<(const Robot& other) const {
      return std::tie(m_id, m_angle, static_cast<const Entity<PT>&>(*this)) <
             std::tie(other.m_id, other.m_angle, static_cast<const Entity<PT>&>(other));
    }
    constexpr bool operator==(const Robot& other) const {
      return std::tie(m_id, m_angle, static_cast<const Entity<PT>&>(*this)) ==
             std::tie(other.m_id, other.m_angle, static_cast<const Entity<PT>&>(other));
    }
    constexpr bool operator!=(const Robot& other) const {
      return !(other == *this);
    }
  };
} // namespace Common

#ifndef QT_NO_DEBUG_STREAM
template <class PT>
QDebug operator<<(QDebug dbg, const Common::RawRobot<PT>& robot) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << Qt::fixed << qSetRealNumberPrecision(2);
  dbg << "Robot(id(" << robot.id() << "), angle(" << Geometry::radiansToDegrees(robot.angle())
      << "), position(" << robot.position().x() << ',' << robot.position().y() << "))";
  return dbg;
}
#endif

#endif // SOCCER_COMMON_ROBOT_H
