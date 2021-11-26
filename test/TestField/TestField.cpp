#include "TestField.h"

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
  using Field = Common::Field<QPoint>;

  constexpr const Field field(true, 150, 130, 10, 40, 15, 70);

  static_assert(field.length() == 150);
  static_assert(field.width() == 130);

  static_assert(field.goalDepth() == 10);
  static_assert(field.goalWidth() == 40);

  static_assert(field.penaltyAreaDepth() == 15);
  static_assert(field.penaltyAreaWidth() == 70);

  static_assert(field.size() == QPoint(170, 130));

  static_assert(field.min() == QPoint(-75, -65));
  static_assert(field.center() == QPoint(0, 0));
  static_assert(field.max() == QPoint(75, 65));

  static_assert(field.bottomLeft() == QPoint(-75, -65));
  static_assert(field.bottomCenter() == QPoint(0, -65));
  static_assert(field.bottomRight() == QPoint(+75, -65));

  static_assert(field.topLeft() == QPoint(-75, +65));
  static_assert(field.topCenter() == QPoint(0, +65));
  static_assert(field.topRight() == QPoint(+75, +65));

  static_assert(field.allyGoalInsideBottom() == QPoint(-85, -20));
  static_assert(field.rightGoalInsideBottom() == QPoint(+85, -20));
  static_assert(field.allyGoalInsideBottom() == QPoint(-85, -20));
  static_assert(field.enemyGoalInsideBottom() == QPoint(+85, -20));

  static_assert(field.leftGoalInsideCenter() == QPoint(-85, 0));
  static_assert(field.rightGoalInsideCenter() == QPoint(+85, 0));
  static_assert(field.allyGoalInsideCenter() == QPoint(-85, 0));
  static_assert(field.enemyGoalInsideCenter() == QPoint(+85, 0));

  static_assert(field.leftGoalInsideTop() == QPoint(-85, +20));
  static_assert(field.rightGoalInsideTop() == QPoint(+85, +20));
  static_assert(field.allyGoalInsideTop() == QPoint(-85, +20));
  static_assert(field.enemyGoalInsideTop() == QPoint(+85, +20));

  static_assert(field.leftGoalOutsideBottom() == QPoint(-75, -20));
  static_assert(field.rightGoalOutsideBottom() == QPoint(+75, -20));
  static_assert(field.allyGoalOutsideBottom() == QPoint(-75, -20));
  static_assert(field.enemyGoalOutsideBottom() == QPoint(+75, -20));

  static_assert(field.leftGoalOutsideCenter() == QPoint(-75, 0));
  static_assert(field.rightGoalOutsideCenter() == QPoint(+75, 0));
  static_assert(field.allyGoalOutsideCenter() == QPoint(-75, 0));
  static_assert(field.enemyGoalOutsideCenter() == QPoint(+75, 0));

  static_assert(field.leftGoalOutsideTop() == QPoint(-75, +20));
  static_assert(field.rightGoalOutsideTop() == QPoint(+75, +20));
  static_assert(field.allyGoalOutsideTop() == QPoint(-75, +20));
  static_assert(field.enemyGoalOutsideTop() == QPoint(+75, +20));

  static_assert(field.leftPenaltyAreaCornerBottom() == QPoint(-60, -35));
  static_assert(field.rightPenaltyAreaCornerBottom() == QPoint(+60, -35));
  static_assert(field.allyPenaltyAreaCornerBottom() == QPoint(-60, -35));
  static_assert(field.enemyPenaltyAreaCornerBottom() == QPoint(+60, -35));

  static_assert(field.leftPenaltyAreaCornerTop() == QPoint(-60, +35));
  static_assert(field.rightPenaltyAreaCornerTop() == QPoint(+60, +35));
  static_assert(field.allyPenaltyAreaCornerTop() == QPoint(-60, +35));
  static_assert(field.enemyPenaltyAreaCornerTop() == QPoint(+60, +35));

  static_assert(!field.leftGoalContains(QPoint(-85, -20)));
  static_assert(!field.leftGoalContains(QPoint(-85, -19)));
  static_assert(field.leftGoalContains(QPoint(-84, -19)));
  static_assert(field.leftGoalContains(QPoint(-80, -15)));
  static_assert(field.leftGoalContains(QPoint(-80, 0)));
  static_assert(field.leftGoalContains(QPoint(-80, +15)));
  static_assert(field.leftGoalContains(QPoint(-84, +19)));
  static_assert(!field.leftGoalContains(QPoint(-85, +19)));
  static_assert(!field.leftGoalContains(QPoint(-85, +20)));

  static_assert(!field.rightGoalContains(QPoint(+85, -20)));
  static_assert(!field.rightGoalContains(QPoint(+85, -19)));
  static_assert(field.rightGoalContains(QPoint(+84, -19)));
  static_assert(field.rightGoalContains(QPoint(+80, -15)));
  static_assert(field.rightGoalContains(QPoint(+80, 0)));
  static_assert(field.rightGoalContains(QPoint(+80, +15)));
  static_assert(field.rightGoalContains(QPoint(+84, +19)));
  static_assert(!field.rightGoalContains(QPoint(+85, +19)));
  static_assert(!field.rightGoalContains(QPoint(+85, +20)));

  static_assert(!field.allyGoalContains(QPoint(-85, -20)));
  static_assert(!field.allyGoalContains(QPoint(-85, -19)));
  static_assert(field.allyGoalContains(QPoint(-84, -19)));
  static_assert(field.allyGoalContains(QPoint(-80, -15)));
  static_assert(field.allyGoalContains(QPoint(-80, 0)));
  static_assert(field.allyGoalContains(QPoint(-80, +15)));
  static_assert(field.allyGoalContains(QPoint(-84, +19)));
  static_assert(!field.allyGoalContains(QPoint(-85, +19)));
  static_assert(!field.allyGoalContains(QPoint(-85, +20)));

  static_assert(!field.enemyGoalContains(QPoint(+85, -20)));
  static_assert(!field.enemyGoalContains(QPoint(+85, -19)));
  static_assert(field.enemyGoalContains(QPoint(+84, -19)));
  static_assert(field.enemyGoalContains(QPoint(+80, -15)));
  static_assert(field.enemyGoalContains(QPoint(+80, 0)));
  static_assert(field.enemyGoalContains(QPoint(+80, +15)));
  static_assert(field.enemyGoalContains(QPoint(+84, +19)));
  static_assert(!field.enemyGoalContains(QPoint(+85, +19)));
  static_assert(!field.enemyGoalContains(QPoint(+85, +20)));

  static_assert(field.withoutGoalsContains(QPoint(0, 0)));
  static_assert(field.withoutGoalsContains(QPoint(+30, +30)));
  static_assert(field.withoutGoalsContains(QPoint(-30, +30)));
  static_assert(field.withoutGoalsContains(QPoint(-30, -30)));
  static_assert(field.withoutGoalsContains(QPoint(+30, -30)));

  static_assert(!field.contains(QPoint(-85, -20)));
  static_assert(!field.contains(QPoint(-85, -19)));
  static_assert(field.contains(QPoint(-84, -19)));
  static_assert(field.contains(QPoint(-80, -15)));
  static_assert(field.contains(QPoint(-80, 0)));
  static_assert(field.contains(QPoint(-80, +15)));
  static_assert(field.contains(QPoint(-84, +19)));
  static_assert(!field.contains(QPoint(-85, +19)));
  static_assert(!field.contains(QPoint(-85, +20)));
  static_assert(!field.contains(QPoint(+85, -20)));
  static_assert(!field.contains(QPoint(+85, -19)));
  static_assert(field.contains(QPoint(+84, -19)));
  static_assert(field.contains(QPoint(+80, -15)));
  static_assert(field.contains(QPoint(+80, 0)));
  static_assert(field.contains(QPoint(+80, +15)));
  static_assert(field.contains(QPoint(+84, +19)));
  static_assert(!field.contains(QPoint(+85, +19)));
  static_assert(!field.contains(QPoint(+85, +20)));
  static_assert(field.contains(QPoint(0, 0)));
  static_assert(field.contains(QPoint(+30, +30)));
  static_assert(field.contains(QPoint(-30, +30)));
  static_assert(field.contains(QPoint(-30, -30)));
  static_assert(field.contains(QPoint(+30, -30)));

  static_assert(!field.leftSideContains(QPoint(-85, -20)));
  static_assert(!field.leftSideContains(QPoint(-85, -19)));
  static_assert(field.leftSideContains(QPoint(-84, -19)));
  static_assert(field.leftSideContains(QPoint(-80, -15)));
  static_assert(field.leftSideContains(QPoint(-80, 0)));
  static_assert(field.leftSideContains(QPoint(-80, +15)));
  static_assert(field.leftSideContains(QPoint(-84, +19)));
  static_assert(!field.leftSideContains(QPoint(-85, +19)));
  static_assert(!field.leftSideContains(QPoint(-85, +20)));
  static_assert(!field.leftSideContains(QPoint(+85, -20)));
  static_assert(!field.leftSideContains(QPoint(+85, -19)));
  static_assert(!field.leftSideContains(QPoint(+84, -19)));
  static_assert(!field.leftSideContains(QPoint(+80, -15)));
  static_assert(!field.leftSideContains(QPoint(+80, 0)));
  static_assert(!field.leftSideContains(QPoint(+80, +15)));
  static_assert(!field.leftSideContains(QPoint(+84, +19)));
  static_assert(!field.leftSideContains(QPoint(+85, +19)));
  static_assert(!field.leftSideContains(QPoint(+85, +20)));
  static_assert(!field.leftSideContains(QPoint(0, 0)));
  static_assert(!field.leftSideContains(QPoint(+30, +30)));
  static_assert(field.leftSideContains(QPoint(-30, +30)));
  static_assert(field.leftSideContains(QPoint(-30, -30)));
  static_assert(!field.leftSideContains(QPoint(+30, -30)));

  static_assert(!field.rightSideContains(QPoint(-85, -20)));
  static_assert(!field.rightSideContains(QPoint(-85, -19)));
  static_assert(!field.rightSideContains(QPoint(-84, -19)));
  static_assert(!field.rightSideContains(QPoint(-80, -15)));
  static_assert(!field.rightSideContains(QPoint(-80, 0)));
  static_assert(!field.rightSideContains(QPoint(-80, +15)));
  static_assert(!field.rightSideContains(QPoint(-84, +19)));
  static_assert(!field.rightSideContains(QPoint(-85, +19)));
  static_assert(!field.rightSideContains(QPoint(-85, +20)));
  static_assert(!field.rightSideContains(QPoint(+85, -20)));
  static_assert(!field.rightSideContains(QPoint(+85, -19)));
  static_assert(field.rightSideContains(QPoint(+84, -19)));
  static_assert(field.rightSideContains(QPoint(+80, -15)));
  static_assert(field.rightSideContains(QPoint(+80, 0)));
  static_assert(field.rightSideContains(QPoint(+80, +15)));
  static_assert(field.rightSideContains(QPoint(+84, +19)));
  static_assert(!field.rightSideContains(QPoint(+85, +19)));
  static_assert(!field.rightSideContains(QPoint(+85, +20)));
  static_assert(!field.rightSideContains(QPoint(0, 0)));
  static_assert(field.rightSideContains(QPoint(+30, +30)));
  static_assert(!field.rightSideContains(QPoint(-30, +30)));
  static_assert(!field.rightSideContains(QPoint(-30, -30)));
  static_assert(field.rightSideContains(QPoint(+30, -30)));

  static_assert(!field.allySideContains(QPoint(-85, -20)));
  static_assert(!field.allySideContains(QPoint(-85, -19)));
  static_assert(field.allySideContains(QPoint(-84, -19)));
  static_assert(field.allySideContains(QPoint(-80, -15)));
  static_assert(field.allySideContains(QPoint(-80, 0)));
  static_assert(field.allySideContains(QPoint(-80, +15)));
  static_assert(field.allySideContains(QPoint(-84, +19)));
  static_assert(!field.allySideContains(QPoint(-85, +19)));
  static_assert(!field.allySideContains(QPoint(-85, +20)));
  static_assert(!field.allySideContains(QPoint(+85, -20)));
  static_assert(!field.allySideContains(QPoint(+85, -19)));
  static_assert(!field.allySideContains(QPoint(+84, -19)));
  static_assert(!field.allySideContains(QPoint(+80, -15)));
  static_assert(!field.allySideContains(QPoint(+80, 0)));
  static_assert(!field.allySideContains(QPoint(+80, +15)));
  static_assert(!field.allySideContains(QPoint(+84, +19)));
  static_assert(!field.allySideContains(QPoint(+85, +19)));
  static_assert(!field.allySideContains(QPoint(+85, +20)));
  static_assert(!field.allySideContains(QPoint(0, 0)));
  static_assert(!field.allySideContains(QPoint(+30, +30)));
  static_assert(field.allySideContains(QPoint(-30, +30)));
  static_assert(field.allySideContains(QPoint(-30, -30)));
  static_assert(!field.allySideContains(QPoint(+30, -30)));

  static_assert(!field.enemySideContains(QPoint(-85, -20)));
  static_assert(!field.enemySideContains(QPoint(-85, -19)));
  static_assert(!field.enemySideContains(QPoint(-84, -19)));
  static_assert(!field.enemySideContains(QPoint(-80, -15)));
  static_assert(!field.enemySideContains(QPoint(-80, 0)));
  static_assert(!field.enemySideContains(QPoint(-80, +15)));
  static_assert(!field.enemySideContains(QPoint(-84, +19)));
  static_assert(!field.enemySideContains(QPoint(-85, +19)));
  static_assert(!field.enemySideContains(QPoint(-85, +20)));
  static_assert(!field.enemySideContains(QPoint(+85, -20)));
  static_assert(!field.enemySideContains(QPoint(+85, -19)));
  static_assert(field.enemySideContains(QPoint(+84, -19)));
  static_assert(field.enemySideContains(QPoint(+80, -15)));
  static_assert(field.enemySideContains(QPoint(+80, 0)));
  static_assert(field.enemySideContains(QPoint(+80, +15)));
  static_assert(field.enemySideContains(QPoint(+84, +19)));
  static_assert(!field.enemySideContains(QPoint(+85, +19)));
  static_assert(!field.enemySideContains(QPoint(+85, +20)));
  static_assert(!field.enemySideContains(QPoint(0, 0)));
  static_assert(field.enemySideContains(QPoint(+30, +30)));
  static_assert(!field.enemySideContains(QPoint(-30, +30)));
  static_assert(!field.enemySideContains(QPoint(-30, -30)));
  static_assert(field.enemySideContains(QPoint(+30, -30)));

  static_assert(field.leftPenaltyAreaContains(QPoint(-70, -15)));
  static_assert(field.leftPenaltyAreaContains(QPoint(-70, 0)));
  static_assert(field.leftPenaltyAreaContains(QPoint(-70, +15)));

  static_assert(field.rightPenaltyAreaContains(QPoint(+70, -15)));
  static_assert(field.rightPenaltyAreaContains(QPoint(+70, 0)));
  static_assert(field.rightPenaltyAreaContains(QPoint(+70, +15)));

  static_assert(field.allyPenaltyAreaContains(QPoint(-70, -15)));
  static_assert(field.allyPenaltyAreaContains(QPoint(-70, 0)));
  static_assert(field.allyPenaltyAreaContains(QPoint(-70, +15)));

  static_assert(field.enemyPenaltyAreaContains(QPoint(+70, -15)));
  static_assert(field.enemyPenaltyAreaContains(QPoint(+70, 0)));
  static_assert(field.enemyPenaltyAreaContains(QPoint(+70, +15)));

  static_assert(!field.contains(QPoint(0, 75), 20));
  static_assert(!field.contains(QPoint(0, -75), 20));
  static_assert(field.contains(QPoint(0, 75), 22));
  static_assert(field.contains(QPoint(0, -75), 22));
}

QTEST_MAIN(TestField)
