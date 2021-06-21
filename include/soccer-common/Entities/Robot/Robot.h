#ifndef SOCCER_COMMON_ROBOT_H
#define SOCCER_COMMON_ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

namespace Common {
  class RawRobot : virtual public RawEntity {
   protected:
    int m_id;
    qreal m_angle;

   public:
    RawRobot(int id, qreal angle, const RawEntity& rawEntity);
    RawRobot(int id, qreal angle, const QPointF& position);

    using RawEntity::position;
    using RawEntity::operator const QPointF&;

    int id() const;
    qreal angle() const;

    bool operator<(const RawRobot& other) const;
    bool operator==(const RawRobot& other) const;
    bool operator!=(const RawRobot& other) const;
  };

  class Robot : public Entity, public RawRobot {
   protected:
   public:
    Robot(int id, qreal angle, const Entity& entity);
    Robot(const RawRobot& rawRobot, const QPointF& velocity, const QPointF& acceleration);
    Robot(int id,
          qreal angle,
          const QPointF& position,
          const QPointF& velocity,
          const QPointF& acceleration);

    using RawRobot::id;
    using RawRobot::angle;
    using Entity::position;
    using Entity::operator const QPointF&;
    using Entity::velocity;
    using Entity::acceleration;

    bool operator<(const Robot& other) const;
    bool operator==(const Robot& other) const;
    bool operator!=(const Robot& other) const;
  };
} // namespace Common

#endif // SOCCER_COMMON_ROBOT_H
