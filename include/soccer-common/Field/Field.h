#ifndef SOCCER_COMMON_FIELD_H
#define SOCCER_COMMON_FIELD_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

#include "soccer-common/Geometry/Geometry.h"

namespace Common {
  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @tparam T Type of values. Default is the PT type of coordinates.
   * @note The center/middle of the field is defined in (0, 0).
   */
  template <class PT, class T = Geometry2D::CoordType<PT>>
  class Field {
   public:
    constexpr Field(bool isAttackingToRight,
                    const T& length,
                    const T& width,
                    const T& goalDepth,
                    const T& goalWidth,
                    const T& penaltyAreaDepth,
                    const T& penaltyAreaWidth) :
        m_isAttackingToRight(isAttackingToRight),
        m_length(length),
        m_width(width),
        m_goalDepth(goalDepth),
        m_goalWidth(goalWidth),
        m_penaltyAreaDepth(penaltyAreaDepth),
        m_penaltyAreaWidth(penaltyAreaWidth) {
    }

    [[nodiscard]] constexpr bool isAttackingToRight() const {
      return m_isAttackingToRight;
    }

    constexpr T length() const {
      return m_length;
    }

    constexpr T width() const {
      return m_width;
    }

    constexpr T goalDepth() const {
      return m_goalDepth;
    }

    constexpr T goalWidth() const {
      return m_goalWidth;
    }

    constexpr T penaltyAreaDepth() const {
      return 10;
    }

    constexpr T penaltyAreaWidth() const {
      return m_penaltyAreaWidth;
    }

    // size is equals to the field size + goals depth.
    constexpr PT size() const {
      return PT(length() + 2 * goalDepth(), width());
    }

    // field limits:

    // min is the left-lower position without the goal depth.
    constexpr PT min() const {
      return PT(-(length() / 2), -(width() / 2));
    }

    // center in (0, 0).
    constexpr PT center() const {
      return PT(0, 0);
    }

    // max is the right-upper position without the goal depth.
    constexpr PT max() const {
      return PT(+(length() / 2), +(width() / 2));
    }

    // field corners:

    // equals to min().
    constexpr PT bottomLeft() const {
      return min();
    }

    constexpr PT bottomCenter() const {
      return PT(center().x(), min().y());
    }

    constexpr PT bottomRight() const {
      return PT(max().x(), min().y());
    }

    constexpr PT topLeft() const {
      return PT(min().x(), max().y());
    }

    constexpr PT topCenter() const {
      return PT(center().x(), max().y());
    }

    // equals to max().
    constexpr PT topRight() const {
      return max();
    }

    // goal inside bottom:

    // left goalkeeper goal inside bottom.
    constexpr PT leftGoalInsideBottom() const {
      return PT(min().x() - goalDepth(), center().y() - (goalWidth() / 2));
    }

    // right goalkeeper goal inside bottom.
    constexpr PT rightGoalInsideBottom() const {
      return PT(max().x() + goalDepth(), center().y() - (goalWidth() / 2));
    }

    // our goalkeeper goal inside bottom.
    constexpr PT allyGoalInsideBottom() const {
      return isAttackingToRight() ? leftGoalInsideBottom() : rightGoalInsideBottom();
    }

    // enemy goalkeeper goal inside bottom.
    constexpr PT enemyGoalInsideBottom() const {
      return isAttackingToRight() ? rightGoalInsideBottom() : leftGoalInsideBottom();
    }

    // goal inside center:

    // left goalkeeper goal inside center.
    constexpr PT leftGoalInsideCenter() const {
      return PT(min().x() - goalDepth(), center().y());
    }

    // right goalkeeper goal inside center.
    constexpr PT rightGoalInsideCenter() const {
      return PT(max().x() + goalDepth(), center().y());
    }

    // our goalkeeper goal inside center.
    constexpr PT allyGoalInsideCenter() const {
      return isAttackingToRight() ? leftGoalInsideCenter() : rightGoalInsideCenter();
    }

    // enemy goalkeeper goal inside center.
    constexpr PT enemyGoalInsideCenter() const {
      return isAttackingToRight() ? rightGoalInsideCenter() : leftGoalInsideCenter();
    }

    // goal inside top:

    // left goalkeeper goal inside top.
    constexpr PT leftGoalInsideTop() const {
      return PT(min().x() - goalDepth(), center().y() + (goalWidth() / 2));
    }

    // right goalkeeper goal inside top.
    constexpr PT rightGoalInsideTop() const {
      return PT(max().x() + goalDepth(), center().y() + (goalWidth() / 2));
    }

    // our goalkeeper goal inside top.
    constexpr PT allyGoalInsideTop() const {
      return isAttackingToRight() ? leftGoalInsideTop() : rightGoalInsideTop();
    }

    // enemy goalkeeper goal inside top.
    constexpr PT enemyGoalInsideTop() const {
      return isAttackingToRight() ? rightGoalInsideTop() : leftGoalInsideTop();
    }

    // goal outside bottom:

    // left goalkeeper goal outside bottom.
    constexpr PT leftGoalOutsideBottom() const {
      return PT(min().x(), center().y() - (goalWidth() / 2));
    }

    // right goalkeeper goal outside Bottom.
    constexpr PT rightGoalOutsideBottom() const {
      return PT(max().x(), center().y() - (goalWidth() / 2));
    }

    // our goalkeeper goal outside bottom.
    constexpr PT allyGoalOutsideBottom() const {
      return isAttackingToRight() ? leftGoalOutsideBottom() : rightGoalOutsideBottom();
    }

    // enemy goalkeeper goal outside bottom.
    constexpr PT enemyGoalOutsideBottom() const {
      return isAttackingToRight() ? rightGoalOutsideBottom() : leftGoalOutsideBottom();
    }

    // goal outside center:

    // left goalkeeper goal outside center.
    constexpr PT leftGoalOutsideCenter() const {
      return PT(min().x(), center().y());
    }

    // right goalkeeper goal outside center.
    constexpr PT rightGoalOutsideCenter() const {
      return PT(max().x(), center().y());
    }

    // our goalkeeper goal outside center.
    constexpr PT allyGoalOutsideCenter() const {
      return isAttackingToRight() ? leftGoalOutsideCenter() : rightGoalOutsideCenter();
    }

    // enemy goalkeeper goal outside center.
    constexpr PT enemyGoalOutsideCenter() const {
      return isAttackingToRight() ? rightGoalOutsideCenter() : leftGoalOutsideCenter();
    }

    // goal outside top:

    // left goalkeeper goal outside top.
    constexpr PT leftGoalOutsideTop() const {
      return PT(min().x(), center().y() + (goalWidth() / 2));
    }

    // right goalkeeper goal outside top.
    constexpr PT rightGoalOutsideTop() const {
      return PT(max().x(), center().y() + (goalWidth() / 2));
    }

    // our goalkeeper goal outside top.
    constexpr PT allyGoalOutsideTop() const {
      return isAttackingToRight() ? leftGoalOutsideTop() : rightGoalOutsideTop();
    }

    // enemy goalkeeper goal outside top.
    constexpr PT enemyGoalOutsideTop() const {
      return isAttackingToRight() ? rightGoalOutsideTop() : leftGoalOutsideTop();
    }

    // penalty area corner bottom:

    // left goalkeeper penalty area corner bottom.
    constexpr PT leftPenaltyAreaCornerBottom() const {
      return PT(min().x() + penaltyAreaDepth(), center().y() - (penaltyAreaWidth() / 2));
    }

    // right goalkeeper penalty area corner bottom.
    constexpr PT rightPenaltyAreaCornerBottom() const {
      return PT(max().x() - penaltyAreaDepth(), center().y() - (penaltyAreaWidth() / 2));
    }

    // our goalkeeper penalty area corner bottom.
    constexpr PT allyPenaltyAreaCornerBottom() const {
      return isAttackingToRight() ? leftPenaltyAreaCornerBottom() : rightPenaltyAreaCornerBottom();
    }

    // enemy goalkeeper penalty area corner bottom.
    constexpr PT enemyPenaltyAreaCornerBottom() const {
      return isAttackingToRight() ? rightPenaltyAreaCornerBottom() : leftPenaltyAreaCornerBottom();
    }

    // penalty area center:

    // left goalkeeper penalty area center.
    constexpr PT leftPenaltyAreaCenter() const {
      return PT(min().x() + penaltyAreaDepth(), center().y());
    }

    // right goalkeeper penalty area center.
    constexpr PT rightPenaltyAreaCenter() const {
      return PT(max().x() - penaltyAreaDepth(), center().y());
    }

    // our goalkeeper penalty area center.
    constexpr PT allyPenaltyAreaCenter() const {
      return isAttackingToRight() ? leftPenaltyAreaCenter() : rightPenaltyAreaCenter();
    }

    // enemy goalkeeper penalty area center.
    constexpr PT enemyPenaltyAreaCenter() const {
      return isAttackingToRight() ? rightPenaltyAreaCenter() : leftPenaltyAreaCenter();
    }

    // penalty area corner top:

    // left goalkeeper penalty area corner top.
    constexpr PT leftPenaltyAreaCornerTop() const {
      return PT(min().x() + penaltyAreaDepth(), center().y() + (penaltyAreaWidth() / 2));
    }

    // right goalkeeper penalty area corner top.
    constexpr PT rightPenaltyAreaCornerTop() const {
      return PT(max().x() - penaltyAreaDepth(), center().y() + (penaltyAreaWidth() / 2));
    }

    // our goalkeeper penalty area corner top.
    constexpr PT allyPenaltyAreaCornerTop() const {
      return isAttackingToRight() ? leftPenaltyAreaCornerTop() : rightPenaltyAreaCornerTop();
    }

    // enemy goalkeeper penalty area corner top.
    constexpr PT enemyPenaltyAreaCornerTop() const {
      return isAttackingToRight() ? rightPenaltyAreaCornerTop() : leftPenaltyAreaCornerTop();
    }

    // penalty area goal corner top:

    // left goalkeeper penalty area goal corner top.
    constexpr PT leftPenaltyAreaGoalCornerTop() const {
      return PT(min().x(), (penaltyAreaWidth() / 2));
    }

    // right goalkeeper penalty area goal corner top.
    constexpr PT rightPenaltyAreaGoalCornerTop() const {
      return PT(max().x(), (penaltyAreaWidth() / 2));
    }

    // our goalkeeper penalty area goal corner top.
    constexpr PT allyPenaltyAreaGoalCornerTop() const {
      return isAttackingToRight() ? leftPenaltyAreaGoalCornerTop() :
                                    rightPenaltyAreaGoalCornerTop();
    }

    // enemy goalkeeper penalty area goal corner top.
    constexpr PT enemyPenaltyAreaGoalCornerTop() const {
      return isAttackingToRight() ? rightPenaltyAreaGoalCornerTop() :
                                    leftPenaltyAreaGoalCornerTop();
    }

    // penalty area goal corner bottom:

    // left goalkeeper penalty area goal corner bottom.
    constexpr PT leftPenaltyAreaGoalCornerBottom() const {
      return PT(min().x(), -(penaltyAreaWidth() / 2));
    }

    // right goalkeeper penalty area goal corner bottom.
    constexpr PT rightPenaltyAreaGoalCornerBottom() const {
      return PT(max().x(), -(penaltyAreaWidth() / 2));
    }

    // our goalkeeper penalty area goal corner bottom.
    constexpr PT allyPenaltyAreaGoalCornerBottom() const {
      return isAttackingToRight() ? leftPenaltyAreaGoalCornerBottom() :
                                    rightPenaltyAreaGoalCornerBottom();
    }

    // enemy goalkeeper penalty area goal corner bottom.
    constexpr PT enemyPenaltyAreaGoalCornerBottom() const {
      return isAttackingToRight() ? rightPenaltyAreaGoalCornerBottom() :
                                    leftPenaltyAreaGoalCornerBottom();
    }

    static constexpr PT leftDirection() {
      return PT(-1, 0);
    }

    static constexpr PT rightDirection() {
      return PT(+1, 0);
    }

    constexpr PT attackDirection() const {
      return isAttackingToRight() ? rightDirection() : leftDirection();
    }

    constexpr PT defendDirection() const {
      return isAttackingToRight() ? leftDirection() : rightDirection();
    }

    // goal contains:

    constexpr bool leftGoalContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(leftGoalInsideBottom(), leftGoalOutsideTop(), point, radius);
      } else {
        return contains(leftGoalInsideBottom(), leftGoalOutsideTop(), point);
      }
    }

    constexpr bool rightGoalContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(rightGoalOutsideBottom(), rightGoalInsideTop(), point, radius);
      } else {
        return contains(rightGoalOutsideBottom(), rightGoalInsideTop(), point);
      }
    }

    constexpr bool allyGoalContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? leftGoalContains(point, radius) :
                                    rightGoalContains(point, radius);
    }

    constexpr bool enemyGoalContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? rightGoalContains(point, radius) :
                                    leftGoalContains(point, radius);
    }

    // without goals contains:

    constexpr bool withoutGoalsContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(bottomLeft(), topRight(), point, radius);
      } else {
        return contains(bottomLeft(), topRight(), point);
      }
    }

    // contains:

    constexpr bool contains(const PT& point, T radius = 0) const {
      return leftGoalContains(point, radius) || withoutGoalsContains(point, radius) ||
             rightGoalContains(point, radius);
    }

    // side contains:

    constexpr bool leftSideContains(const PT& point, T radius = 0) const {
      if (radius) {
        return leftGoalContains(point, radius) ||
               contains(bottomLeft(), topCenter(), point, radius);
      } else {
        return leftGoalContains(point, radius) || contains(bottomLeft(), topCenter(), point);
      }
    }

    constexpr bool rightSideContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(bottomCenter(), topRight(), point, radius) ||
               rightGoalContains(point, radius);
      } else {
        return contains(bottomCenter(), topRight(), point) || rightGoalContains(point, radius);
      }
    }

    constexpr bool allySideContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? leftSideContains(point, radius) :
                                    rightSideContains(point, radius);
    }

    constexpr bool enemySideContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? rightSideContains(point, radius) :
                                    leftSideContains(point, radius);
    }

    // penalty area contains:

    constexpr bool leftPenaltyAreaContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(PT(min().x(), leftPenaltyAreaCornerBottom().y()),
                        leftPenaltyAreaCornerTop(),
                        point,
                        radius);
      } else {
        return contains(PT(min().x(), leftPenaltyAreaCornerBottom().y()),
                        leftPenaltyAreaCornerTop(),
                        point);
      }
    }

    constexpr bool rightPenaltyAreaContains(const PT& point, T radius = 0) const {
      if (radius) {
        return contains(rightPenaltyAreaCornerBottom(),
                        PT(max().x(), rightPenaltyAreaCornerTop().y()),
                        point,
                        radius);
      } else {
        return contains(rightPenaltyAreaCornerBottom(),
                        PT(max().x(), rightPenaltyAreaCornerTop().y()),
                        point);
      }
    }

    constexpr bool allyPenaltyAreaContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? leftPenaltyAreaContains(point, radius) :
                                    rightPenaltyAreaContains(point, radius);
    }

    constexpr bool enemyPenaltyAreaContains(const PT& point, T radius = 0) const {
      return isAttackingToRight() ? rightPenaltyAreaContains(point, radius) :
                                    leftPenaltyAreaContains(point, radius);
    }

   protected:
    // strictly contains:
    static constexpr bool contains(const PT& bottomLeft, const PT& topRight, const PT& point) {
      return (bottomLeft.x() < point.x() && point.x() < topRight.x()) &&
             (bottomLeft.y() < point.y() && point.y() < topRight.y());
    }

    static constexpr bool contains(const PT& a1, const PT& a2, const PT& point, T radius) {
      const PT& b1(point - PT(radius / 2, radius / 2));
      const PT& b2(point + PT(radius / 2, radius / 2));
      return ((b1.x() < a2.x()) && (a1.x() < b2.x())) && ((b1.y() < a2.y()) && (a1.y() < b2.y()));
    }

   private:
    bool m_isAttackingToRight;

    T m_length;
    T m_width;
    T m_goalDepth;
    T m_goalWidth;
    T m_penaltyAreaDepth;
    T m_penaltyAreaWidth;
  };
} // namespace Common

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_FIELD_H
