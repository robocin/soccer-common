#ifndef SOCCER_COMMON_BALL_H
#define SOCCER_COMMON_BALL_H

#include "soccer-common/Entities/Entity/Entity.h"

/**
 * @brief Ball class that holds only telemetry data
 * 
 */
class RawBall : virtual public RawEntity {
 public:

  /**
   * @brief Class constructor
   * 
   * @param position - Current ball position
   */
  explicit RawBall(const QPointF& position);
};

/**
 * @brief Ball class that holds telemetry data plus calculated values. 
 * 
 */
class Ball : public Entity, public RawBall {
 public:

  /**
   * @brief Class constructor
   * 
   * @param position - Current ball position 
   * @param velocity - Current calculated ball velocity
   * @param acceleration - Current calculated ball acceleration
   */
  Ball(const QPointF& position, const QPointF& velocity, const QPointF& acceleration);
};

#endif // SOCCER_COMMON_BALL_H
