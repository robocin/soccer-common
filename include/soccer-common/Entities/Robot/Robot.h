#ifndef SOCCER_COMMON_ROBOT_H
#define SOCCER_COMMON_ROBOT_H

#include "soccer-common/Entities/Entity/Entity.h"

/**
 * @brief Robot class that holds only telemetry data.
 * 
 */
class RawRobot : virtual public RawEntity {
  int m_id; /**< robot id */
  qreal m_angle; /**< robot angle //TODO: isso está descritivo o suficiente? me parece que não (?) */

 public:

  /**
   * @brief Class constructor
   * 
   * @param id - robot id 
   * @param angle - Current robot angle 
   * @param position - Current robot position
   */
  RawRobot(int id, qreal angle, const QPointF& position);

  /**
   * @return Robot id
   *
   */
  int id() const; 

  /**
   * @return Current robot angle
   *
   */
  qreal angle() const; 
};

/**
 * @brief Robot class that holds telemetry data plus calculated values. 
 * 
 */
class Robot : public Entity, public RawRobot {
  qreal m_angularVelocity; /**< calculated angular robot velocity */

 public:

  /**
   * @brief Class constructor
   * 
   * @param id - Robot id 
   * @param position - Current entity position
   * @param velocity - Current calculated entity velocity
   * @param angularVelocity - Current calculated entity angular velocity
   */
  Robot(int id,
        qreal angle,
        const QPointF& position,
        const QPointF& velocity,
        const QPointF& acceleration,
        qreal angularVelocity);
/**
 * @return Current calculated entity angularVelocity.
 */
  qreal angularVelocity() const;
};

#endif // SOCCER_COMMON_ROBOT_H
