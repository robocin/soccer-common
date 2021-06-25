#ifndef SOCCER_COMMON_ENTITY_H
#define SOCCER_COMMON_ENTITY_H

#include <QPointF>

/**
 * @brief General raw entity class that holds only telemetry data
 * 
 * @details This is the parent class to all raw entity classes. 
 */
class RawEntity {
  QPointF m_position; /**< Current entity position */

 public:

  /**
   * @brief Class constructor
   * 
   * @param position - Current entity position
   * 
   */  
  explicit RawEntity(const QPointF& position);

  /**
   * @return Current entity position. //TODO: esse comentário...
   */
  const QPointF& position() const;

  /**
   * @return Current entity position. //TODO: ...e esse devem ser assim iguais, ou devem ser de outra forma, ou algum deles não deve existir?
   */
  operator const QPointF&() const;
};

/**
 * @brief General entity class that holds telemetry data plus calculated values.
 * 
 * @details This is the parent class to all game entity classes. 
 * 
 */
class Entity : virtual public RawEntity {
  QPointF m_velocity; /**< Current entity velocity */
  QPointF m_acceleration; /**< Current calculated entity acceleration */

 public:
  /**
   * @brief Class constructor
   * 
   * @param position - Current entity position
   * @param velocity - Current calculated entity velocity
   * @param acceleration - Current calculated entity acceleration
   */
  Entity(const QPointF& position, const QPointF& velocity, const QPointF& acceleration);

  /**
   * @return Current calculated entity velocity.
   */
  const QPointF& velocity() const;

  /**
   * @return Current calculated entity acceleration
   */
  const QPointF& acceleration() const;
};

#endif // SOCCER_COMMON_ENTITY_H
