#ifndef SOCCER_COMMON_ROBOT_H
#define SOCCER_COMMON_ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  template <class PT>
  class RawRobot : virtual public RawEntity<PT> {
   protected:
    int m_id{};
    Geometry2D::CoordType<PT> m_angle{};

   public:
    constexpr RawRobot(int id, Geometry2D::CoordType<PT> angle, const RawEntity<PT>& rawEntity) :
        RawEntity<PT>(rawEntity),
        m_id(id),
        m_angle(angle) {
    }
    constexpr RawRobot(int id, Geometry2D::CoordType<PT> angle, const PT& position) :
        RawRobot(id, angle, RawEntity(position)) {
    }

    [[nodiscard]] constexpr int id() const {
      return m_id;
    }

    [[nodiscard]] constexpr Geometry2D::CoordType<PT> angle() const {
      return m_angle;
    }

    constexpr auto angleTo(const PT& p) const {
      return Geometry2D::angleBetween<PT>(Geometry2D::fromPolar<PT>(m_angle),
                                          p - RawEntity<PT>::m_position);
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
  class Robot : public RawRobot<PT>, public Entity<PT> {
   public:
    constexpr Robot(int id, Geometry2D::CoordType<PT> angle, const Entity<PT>& entity) :
        RawEntity<PT>(entity.position()),
        RawRobot<PT>(id, angle, entity.position()),
        Entity<PT>(entity) {
    }
    constexpr Robot(const RawRobot<PT>& rawRobot, const PT& velocity, const PT& acceleration) :
        Robot(rawRobot.id(),
              rawRobot.angle(),
              Entity(rawRobot.position(), velocity, acceleration)) {
    }
    constexpr Robot(int id,
                    Geometry2D::CoordType<PT> angle,
                    const PT& position,
                    const PT& velocity,
                    const PT& acceleration) :
        Robot(id, angle, Entity(position, velocity, acceleration)) {
    }

    constexpr bool operator<(const Robot& other) const {
      return std::tie(RawRobot<PT>::m_id,
                      RawRobot<PT>::m_angle,
                      static_cast<const Entity<PT>&>(*this)) <
             std::tie(other.m_id, other.m_angle, static_cast<const Entity<PT>&>(other));
    }
    constexpr bool operator==(const Robot& other) const {
      return std::tie(RawRobot<PT>::m_id,
                      RawRobot<PT>::m_angle,
                      static_cast<const Entity<PT>&>(*this)) ==
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
      << "), position(" << robot.position().x << ',' << robot.position().y << "))";
  return dbg;
}
#endif

#endif // SOCCER_COMMON_ROBOT_H
