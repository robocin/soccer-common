#include "TestField.h"

#include "soccer-common/Geometry/Geometry.h"

using Point = Point2D<int>;

TestField::TestField() {
}

TestField::~TestField() {
}

void TestField::initTestCase() {
}

void TestField::init() {
}

void TestField::cleanup() {
}

void TestField::cleanupTestCase() {
}

void TestField::test_field_constexpr_withVSS3x3Values() {
  using Field = Common::Field<Point>;

  constexpr const Field field(true, 150, 130, 10, 40, 15, 70);

  static_assert(field.length() == 150);
  static_assert(field.width() == 130);

  static_assert(field.goalDepth() == 10);
  static_assert(field.goalWidth() == 40);

  static_assert(field.penaltyAreaDepth() == 15);
  static_assert(field.penaltyAreaWidth() == 70);

  static_assert(field.size() == Point(170, 130));

  static_assert(field.min() == Point(-75, -65));
  static_assert(field.center() == Point(0, 0));
  static_assert(field.max() == Point(75, 65));

  static_assert(field.bottomLeft() == Point(-75, -65));
  static_assert(field.bottomCenter() == Point(0, -65));
  static_assert(field.bottomRight() == Point(+75, -65));

  static_assert(field.topLeft() == Point(-75, +65));
  static_assert(field.topCenter() == Point(0, +65));
  static_assert(field.topRight() == Point(+75, +65));

  static_assert(field.allyGoalInsideBottom() == Point(-85, -20));
  static_assert(field.rightGoalInsideBottom() == Point(+85, -20));
  static_assert(field.allyGoalInsideBottom() == Point(-85, -20));
  static_assert(field.enemyGoalInsideBottom() == Point(+85, -20));

  static_assert(field.leftGoalInsideCenter() == Point(-85, 0));
  static_assert(field.rightGoalInsideCenter() == Point(+85, 0));
  static_assert(field.allyGoalInsideCenter() == Point(-85, 0));
  static_assert(field.enemyGoalInsideCenter() == Point(+85, 0));

  static_assert(field.leftGoalInsideTop() == Point(-85, +20));
  static_assert(field.rightGoalInsideTop() == Point(+85, +20));
  static_assert(field.allyGoalInsideTop() == Point(-85, +20));
  static_assert(field.enemyGoalInsideTop() == Point(+85, +20));

  static_assert(field.leftGoalOutsideBottom() == Point(-75, -20));
  static_assert(field.rightGoalOutsideBottom() == Point(+75, -20));
  static_assert(field.allyGoalOutsideBottom() == Point(-75, -20));
  static_assert(field.enemyGoalOutsideBottom() == Point(+75, -20));

  static_assert(field.leftGoalOutsideCenter() == Point(-75, 0));
  static_assert(field.rightGoalOutsideCenter() == Point(+75, 0));
  static_assert(field.allyGoalOutsideCenter() == Point(-75, 0));
  static_assert(field.enemyGoalOutsideCenter() == Point(+75, 0));

  static_assert(field.leftGoalOutsideTop() == Point(-75, +20));
  static_assert(field.rightGoalOutsideTop() == Point(+75, +20));
  static_assert(field.allyGoalOutsideTop() == Point(-75, +20));
  static_assert(field.enemyGoalOutsideTop() == Point(+75, +20));

  static_assert(field.leftPenaltyAreaCornerBottom() == Point(-60, -35));
  static_assert(field.rightPenaltyAreaCornerBottom() == Point(+60, -35));
  static_assert(field.allyPenaltyAreaCornerBottom() == Point(-60, -35));
  static_assert(field.enemyPenaltyAreaCornerBottom() == Point(+60, -35));

  static_assert(field.leftPenaltyAreaCenter() == Point(-60, 0));
  static_assert(field.rightPenaltyAreaCenter() == Point(+60, 0));
  static_assert(field.allyPenaltyAreaCenter() == Point(-60, 0));
  static_assert(field.enemyPenaltyAreaCenter() == Point(+60, 0));

  static_assert(field.leftPenaltyAreaCornerTop() == Point(-60, +35));
  static_assert(field.rightPenaltyAreaCornerTop() == Point(+60, +35));
  static_assert(field.allyPenaltyAreaCornerTop() == Point(-60, +35));
  static_assert(field.enemyPenaltyAreaCornerTop() == Point(+60, +35));

  static_assert(field.leftPenaltyAreaGoalCornerTop() == Point(-75, +35));
  static_assert(field.rightPenaltyAreaGoalCornerTop() == Point(+75, +35));
  static_assert(field.allyPenaltyAreaGoalCornerTop() == Point(-75, +35));
  static_assert(field.enemyPenaltyAreaGoalCornerTop() == Point(+75, +35));

  static_assert(field.leftPenaltyAreaGoalCornerBottom() == Point(-75, -35));
  static_assert(field.rightPenaltyAreaGoalCornerBottom() == Point(+75, -35));
  static_assert(field.allyPenaltyAreaGoalCornerBottom() == Point(-75, -35));
  static_assert(field.enemyPenaltyAreaGoalCornerBottom() == Point(+75, -35));

  static_assert(Field::leftDirection() == Point(-1, 0));
  static_assert(Field::rightDirection() == Point(+1, 0));
  static_assert(field.attackDirection() == Point(+1, 0));
  static_assert(field.defendDirection() == Point(-1, 0));

  static_assert(!field.leftGoalContains(Point(-85, -20)));
  static_assert(!field.leftGoalContains(Point(-85, -19)));
  static_assert(field.leftGoalContains(Point(-84, -19)));
  static_assert(field.leftGoalContains(Point(-80, -15)));
  static_assert(field.leftGoalContains(Point(-80, 0)));
  static_assert(field.leftGoalContains(Point(-80, +15)));
  static_assert(field.leftGoalContains(Point(-84, +19)));
  static_assert(!field.leftGoalContains(Point(-85, +19)));
  static_assert(!field.leftGoalContains(Point(-85, +20)));

  static_assert(!field.rightGoalContains(Point(+85, -20)));
  static_assert(!field.rightGoalContains(Point(+85, -19)));
  static_assert(field.rightGoalContains(Point(+84, -19)));
  static_assert(field.rightGoalContains(Point(+80, -15)));
  static_assert(field.rightGoalContains(Point(+80, 0)));
  static_assert(field.rightGoalContains(Point(+80, +15)));
  static_assert(field.rightGoalContains(Point(+84, +19)));
  static_assert(!field.rightGoalContains(Point(+85, +19)));
  static_assert(!field.rightGoalContains(Point(+85, +20)));

  static_assert(!field.allyGoalContains(Point(-85, -20)));
  static_assert(!field.allyGoalContains(Point(-85, -19)));
  static_assert(field.allyGoalContains(Point(-84, -19)));
  static_assert(field.allyGoalContains(Point(-80, -15)));
  static_assert(field.allyGoalContains(Point(-80, 0)));
  static_assert(field.allyGoalContains(Point(-80, +15)));
  static_assert(field.allyGoalContains(Point(-84, +19)));
  static_assert(!field.allyGoalContains(Point(-85, +19)));
  static_assert(!field.allyGoalContains(Point(-85, +20)));

  static_assert(!field.enemyGoalContains(Point(+85, -20)));
  static_assert(!field.enemyGoalContains(Point(+85, -19)));
  static_assert(field.enemyGoalContains(Point(+84, -19)));
  static_assert(field.enemyGoalContains(Point(+80, -15)));
  static_assert(field.enemyGoalContains(Point(+80, 0)));
  static_assert(field.enemyGoalContains(Point(+80, +15)));
  static_assert(field.enemyGoalContains(Point(+84, +19)));
  static_assert(!field.enemyGoalContains(Point(+85, +19)));
  static_assert(!field.enemyGoalContains(Point(+85, +20)));

  static_assert(field.withoutGoalsContains(Point(0, 0)));
  static_assert(field.withoutGoalsContains(Point(+30, +30)));
  static_assert(field.withoutGoalsContains(Point(-30, +30)));
  static_assert(field.withoutGoalsContains(Point(-30, -30)));
  static_assert(field.withoutGoalsContains(Point(+30, -30)));

  static_assert(!field.contains(Point(-85, -20)));
  static_assert(!field.contains(Point(-85, -19)));
  static_assert(field.contains(Point(-84, -19)));
  static_assert(field.contains(Point(-80, -15)));
  static_assert(field.contains(Point(-80, 0)));
  static_assert(field.contains(Point(-80, +15)));
  static_assert(field.contains(Point(-84, +19)));
  static_assert(!field.contains(Point(-85, +19)));
  static_assert(!field.contains(Point(-85, +20)));
  static_assert(!field.contains(Point(+85, -20)));
  static_assert(!field.contains(Point(+85, -19)));
  static_assert(field.contains(Point(+84, -19)));
  static_assert(field.contains(Point(+80, -15)));
  static_assert(field.contains(Point(+80, 0)));
  static_assert(field.contains(Point(+80, +15)));
  static_assert(field.contains(Point(+84, +19)));
  static_assert(!field.contains(Point(+85, +19)));
  static_assert(!field.contains(Point(+85, +20)));
  static_assert(field.contains(Point(0, 0)));
  static_assert(field.contains(Point(+30, +30)));
  static_assert(field.contains(Point(-30, +30)));
  static_assert(field.contains(Point(-30, -30)));
  static_assert(field.contains(Point(+30, -30)));

  static_assert(!field.leftSideContains(Point(-85, -20)));
  static_assert(!field.leftSideContains(Point(-85, -19)));
  static_assert(field.leftSideContains(Point(-84, -19)));
  static_assert(field.leftSideContains(Point(-80, -15)));
  static_assert(field.leftSideContains(Point(-80, 0)));
  static_assert(field.leftSideContains(Point(-80, +15)));
  static_assert(field.leftSideContains(Point(-84, +19)));
  static_assert(!field.leftSideContains(Point(-85, +19)));
  static_assert(!field.leftSideContains(Point(-85, +20)));
  static_assert(!field.leftSideContains(Point(+85, -20)));
  static_assert(!field.leftSideContains(Point(+85, -19)));
  static_assert(!field.leftSideContains(Point(+84, -19)));
  static_assert(!field.leftSideContains(Point(+80, -15)));
  static_assert(!field.leftSideContains(Point(+80, 0)));
  static_assert(!field.leftSideContains(Point(+80, +15)));
  static_assert(!field.leftSideContains(Point(+84, +19)));
  static_assert(!field.leftSideContains(Point(+85, +19)));
  static_assert(!field.leftSideContains(Point(+85, +20)));
  static_assert(!field.leftSideContains(Point(0, 0)));
  static_assert(!field.leftSideContains(Point(+30, +30)));
  static_assert(field.leftSideContains(Point(-30, +30)));
  static_assert(field.leftSideContains(Point(-30, -30)));
  static_assert(!field.leftSideContains(Point(+30, -30)));

  static_assert(!field.rightSideContains(Point(-85, -20)));
  static_assert(!field.rightSideContains(Point(-85, -19)));
  static_assert(!field.rightSideContains(Point(-84, -19)));
  static_assert(!field.rightSideContains(Point(-80, -15)));
  static_assert(!field.rightSideContains(Point(-80, 0)));
  static_assert(!field.rightSideContains(Point(-80, +15)));
  static_assert(!field.rightSideContains(Point(-84, +19)));
  static_assert(!field.rightSideContains(Point(-85, +19)));
  static_assert(!field.rightSideContains(Point(-85, +20)));
  static_assert(!field.rightSideContains(Point(+85, -20)));
  static_assert(!field.rightSideContains(Point(+85, -19)));
  static_assert(field.rightSideContains(Point(+84, -19)));
  static_assert(field.rightSideContains(Point(+80, -15)));
  static_assert(field.rightSideContains(Point(+80, 0)));
  static_assert(field.rightSideContains(Point(+80, +15)));
  static_assert(field.rightSideContains(Point(+84, +19)));
  static_assert(!field.rightSideContains(Point(+85, +19)));
  static_assert(!field.rightSideContains(Point(+85, +20)));
  static_assert(!field.rightSideContains(Point(0, 0)));
  static_assert(field.rightSideContains(Point(+30, +30)));
  static_assert(!field.rightSideContains(Point(-30, +30)));
  static_assert(!field.rightSideContains(Point(-30, -30)));
  static_assert(field.rightSideContains(Point(+30, -30)));

  static_assert(!field.allySideContains(Point(-85, -20)));
  static_assert(!field.allySideContains(Point(-85, -19)));
  static_assert(field.allySideContains(Point(-84, -19)));
  static_assert(field.allySideContains(Point(-80, -15)));
  static_assert(field.allySideContains(Point(-80, 0)));
  static_assert(field.allySideContains(Point(-80, +15)));
  static_assert(field.allySideContains(Point(-84, +19)));
  static_assert(!field.allySideContains(Point(-85, +19)));
  static_assert(!field.allySideContains(Point(-85, +20)));
  static_assert(!field.allySideContains(Point(+85, -20)));
  static_assert(!field.allySideContains(Point(+85, -19)));
  static_assert(!field.allySideContains(Point(+84, -19)));
  static_assert(!field.allySideContains(Point(+80, -15)));
  static_assert(!field.allySideContains(Point(+80, 0)));
  static_assert(!field.allySideContains(Point(+80, +15)));
  static_assert(!field.allySideContains(Point(+84, +19)));
  static_assert(!field.allySideContains(Point(+85, +19)));
  static_assert(!field.allySideContains(Point(+85, +20)));
  static_assert(!field.allySideContains(Point(0, 0)));
  static_assert(!field.allySideContains(Point(+30, +30)));
  static_assert(field.allySideContains(Point(-30, +30)));
  static_assert(field.allySideContains(Point(-30, -30)));
  static_assert(!field.allySideContains(Point(+30, -30)));

  static_assert(!field.enemySideContains(Point(-85, -20)));
  static_assert(!field.enemySideContains(Point(-85, -19)));
  static_assert(!field.enemySideContains(Point(-84, -19)));
  static_assert(!field.enemySideContains(Point(-80, -15)));
  static_assert(!field.enemySideContains(Point(-80, 0)));
  static_assert(!field.enemySideContains(Point(-80, +15)));
  static_assert(!field.enemySideContains(Point(-84, +19)));
  static_assert(!field.enemySideContains(Point(-85, +19)));
  static_assert(!field.enemySideContains(Point(-85, +20)));
  static_assert(!field.enemySideContains(Point(+85, -20)));
  static_assert(!field.enemySideContains(Point(+85, -19)));
  static_assert(field.enemySideContains(Point(+84, -19)));
  static_assert(field.enemySideContains(Point(+80, -15)));
  static_assert(field.enemySideContains(Point(+80, 0)));
  static_assert(field.enemySideContains(Point(+80, +15)));
  static_assert(field.enemySideContains(Point(+84, +19)));
  static_assert(!field.enemySideContains(Point(+85, +19)));
  static_assert(!field.enemySideContains(Point(+85, +20)));
  static_assert(!field.enemySideContains(Point(0, 0)));
  static_assert(field.enemySideContains(Point(+30, +30)));
  static_assert(!field.enemySideContains(Point(-30, +30)));
  static_assert(!field.enemySideContains(Point(-30, -30)));
  static_assert(field.enemySideContains(Point(+30, -30)));

  static_assert(field.leftPenaltyAreaContains(Point(-70, -15)));
  static_assert(field.leftPenaltyAreaContains(Point(-70, 0)));
  static_assert(field.leftPenaltyAreaContains(Point(-70, +15)));

  static_assert(field.rightPenaltyAreaContains(Point(+70, -15)));
  static_assert(field.rightPenaltyAreaContains(Point(+70, 0)));
  static_assert(field.rightPenaltyAreaContains(Point(+70, +15)));

  static_assert(field.allyPenaltyAreaContains(Point(-70, -15)));
  static_assert(field.allyPenaltyAreaContains(Point(-70, 0)));
  static_assert(field.allyPenaltyAreaContains(Point(-70, +15)));

  static_assert(field.enemyPenaltyAreaContains(Point(+70, -15)));
  static_assert(field.enemyPenaltyAreaContains(Point(+70, 0)));
  static_assert(field.enemyPenaltyAreaContains(Point(+70, +15)));

  static_assert(!field.contains(Point(0, 75), 20));
  static_assert(!field.contains(Point(0, -75), 20));
  static_assert(field.contains(Point(0, 75), 22));
  static_assert(field.contains(Point(0, -75), 22));
}

QTEST_MAIN(TestField)
