#ifndef SOCCER_COMMON_ENTITY_H
#define SOCCER_COMMON_ENTITY_H

#include <QPointF>

namespace Common {
  class RawEntity {
   protected:
    QPointF m_position;

   public:
    explicit RawEntity(const QPointF& position);

    const QPointF& position() const;
    operator const QPointF&() const;

    bool operator<(const RawEntity& other) const;
    bool operator==(const RawEntity& other) const;
    bool operator!=(const RawEntity& other) const;
  };

  class Entity : virtual public RawEntity {
   protected:
    QPointF m_velocity;
    QPointF m_acceleration;

   public:
    Entity(const RawEntity& rawEntity, const QPointF& velocity, const QPointF& acceleration);
    Entity(const QPointF& position, const QPointF& velocity, const QPointF& acceleration);

    using RawEntity::position;
    using RawEntity::operator const QPointF&;

    const QPointF& velocity() const;
    const QPointF& acceleration() const;

    bool operator<(const Entity& other) const;
    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
  };
} // namespace Common

#endif // SOCCER_COMMON_ENTITY_H
