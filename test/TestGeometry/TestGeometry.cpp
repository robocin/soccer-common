#include "TestGeometry.h"

using Point = Point2D<int>;
using PointF = Point2D<double>;

TestGeometry::TestGeometry() {
}

TestGeometry::~TestGeometry() {
}

void TestGeometry::initTestCase() {
}

void TestGeometry::init() {
}

void TestGeometry::cleanup() {
}

void TestGeometry::cleanupTestCase() {
}

void TestGeometry::test_radiansToDegrees_whenGivenAFloatingPoint_shouldWork() {
  using namespace Geometry;

  double d15 = 15.0;
  double d15v = radiansToDegrees(PI / 12.0);
  QCOMPARE(d15, d15v);

  float f90 = 90.0f;
  float f90v = radiansToDegrees<float>(PI / 2.0f);
  QCOMPARE(f90, f90v);

  double d30 = 30.0;
  double d30v = radiansToDegrees<double>(PI / 6.0);
  QCOMPARE(d30, d30v);

  long double ld270 = 270.0l;
  long double ld270v = radiansToDegrees<long double>(3.0l * PI / 2.0l);
  QCOMPARE(ld270, ld270v);
}

void TestGeometry::test_degreesToRadians_whenGivenAFloatingPoint_shouldWork() {
  using namespace Geometry;

  float fPI_2 = PI / 2.0f;
  float fPI_2v = degreesToRadians<float>(90.0f);
  QCOMPARE(fPI_2, fPI_2v);

  double dPI_6 = PI / 6.0;
  double dPI_6v = degreesToRadians<double>(30.0);
  QCOMPARE(dPI_6, dPI_6v);

  long double ld3_PI_2 = 3.0l * PI / 2.0l;
  long double ld3_PI_2v = degreesToRadians<long double>(270.0l);
  QCOMPARE(ld3_PI_2, ld3_PI_2v);
}

void TestGeometry::test_operator_degrees_whenGivenAFloatingPoint_shouldWork() {
  using Geometry::operator""_degrees;
  QCOMPARE(PI, 180_degrees);
  QCOMPARE(PI / 2.0, 90_degrees);
  QCOMPARE(PI / 4.0, 45_degrees);
}

void TestGeometry::test_smallestAngleDiff_whenGivenTwoFloatingPointNumbers_shouldWork() {
  using namespace Geometry;

  /* in -180 to +180 range */ {
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(20.0), qDegreesToRadians(45.0)),
             qDegreesToRadians(25));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-45.0), qDegreesToRadians(45.0)),
             qDegreesToRadians(90));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-85.0), qDegreesToRadians(90.0)),
             qDegreesToRadians(175));

    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-95.0), qDegreesToRadians(90.0)),
             qDegreesToRadians(-175));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-45.0), qDegreesToRadians(125.0)),
             qDegreesToRadians(170));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-45.0), qDegreesToRadians(145.0)),
             qDegreesToRadians(-170));

    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-45.0), qDegreesToRadians(125.0)),
             qDegreesToRadians(170));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-45.0), qDegreesToRadians(145.0)),
             qDegreesToRadians(-170));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(29.4803), qDegreesToRadians(-88.6381)),
             qDegreesToRadians(-118.1184));

    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-78.3251), qDegreesToRadians(-159.036)),
             qDegreesToRadians(-80.7109));
  }

  /* wider range */ {
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-70099), qDegreesToRadians(29840)),
             qDegreesToRadians(-141));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(-165313), qDegreesToRadians(33693)),
             qDegreesToRadians(-74));
    QCOMPARE(smallestAngleDiff(qDegreesToRadians(1174), qDegreesToRadians(-154146)),
             qDegreesToRadians(-160));

    QCOMPARE(smallestAngleDiff(qDegreesToRadians(60175), qDegreesToRadians(42213)),
             qDegreesToRadians(38));
  }
}

void TestGeometry::test_normalizeAngle_whenGivenThreeFloatingPointNumbers_shouldWork() {
  using namespace Geometry;
  /* degrees */ {
    QCOMPARE(-10, normalizeAngle(-10, 0, 180));
    QCOMPARE(-45, normalizeAngle(-45, 0, 180));
    QCOMPARE(-90, normalizeAngle(-90, 0, 180));
    QCOMPARE(-90, normalizeAngle(270, 0, 180));
    QCOMPARE(180, normalizeAngle(360 + 180, 0, 180));
  }
  /* radians */ {
    QCOMPARE(degreesToRadians(-10), normalizeAngle(degreesToRadians(-10), 0.0, PI));
    QCOMPARE(degreesToRadians(-45), normalizeAngle(degreesToRadians(-45), 0.0, PI));
    QCOMPARE(degreesToRadians(-90), normalizeAngle(degreesToRadians(-90), 0.0, PI));
    QCOMPARE(degreesToRadians(-90), normalizeAngle(degreesToRadians(270), 0.0, PI));
    QCOMPARE(degreesToRadians(180), normalizeAngle(degreesToRadians(360 + 180), 0.0, PI));
  }
}

void TestGeometry::test_normalizeInPI_whenGivenAFloatingPoint_shouldWork() {
  using namespace Geometry;
  QCOMPARE(0.174533, normalizeInPI(0.174533));
  QCOMPARE(-PI / 4.0, normalizeInPI(-PI / 4.0));
  QCOMPARE(-PI / 2.0, normalizeInPI(-PI / 2.0));
  QCOMPARE(-PI / 2.0, normalizeInPI(3.0 * PI / 2.0));
  QCOMPARE(PI, normalizeInPI(3 * PI));
}

void TestGeometry::test_normalizeIn180_whenGivenAFloatingPoint_shouldWork() {
  using namespace Geometry;
  QCOMPARE(-10, normalizeIn180(-10));
  QCOMPARE(-45, normalizeIn180(-45));
  QCOMPARE(-90, normalizeIn180(-90));
  QCOMPARE(-90, normalizeIn180(270));
  QCOMPARE(180, normalizeIn180(360 + 180));
}

void TestGeometry::test_2D_operatorLess_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    Point iLhsEq(10, 10);
    Point iRhsEq(10, 10);
    QCOMPARE(iLhsEq < iRhsEq, false);

    Point iLhsLessX(5, 10);
    Point iRhsLessX(10, 10);
    QCOMPARE(iLhsLessX < iRhsLessX, true);

    Point iLhsLessY(10, 5);
    Point iRhsLessY(10, 10);
    QCOMPARE(iLhsLessY < iRhsLessY, true);
  }

  /* floating point points. */ {
    PointF fLhsEq(10, 10);
    PointF fRhsEq(10, 10);
    QCOMPARE(fLhsEq < fRhsEq, false);

    PointF fLhsLessX(5, 10);
    PointF fRhsLessX(10, 10);
    QCOMPARE(fLhsLessX < fRhsLessX, true);

    PointF fLhsLessY(10, 5);
    PointF fRhsLessY(10, 10);
    QCOMPARE(fLhsLessY < fRhsLessY, true);
  }
}

void TestGeometry::test_2D_fromPolar_whenGivenAFloatingPoint_shouldWork() {
  using Geometry2D::fromPolar;
  QCOMPARE(PointF(1, 0), fromPolar<PointF>(0));
  QCOMPARE(PointF(0, 1), fromPolar<PointF>(PI / 2));
  QCOMPARE(PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0), fromPolar<PointF>(PI / 4.0));

  QCOMPARE(PointF(1, 0), PointF::fromPolar(0));
  QCOMPARE(PointF(0, 1), PointF::fromPolar(PI / 2));
  QCOMPARE(PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0), PointF::fromPolar(PI / 4.0));
}

void TestGeometry::test_2D_fromPolar_whenGivenTwoFloatingPointNumbers_shouldWork() {
  using Geometry2D::fromPolar;
  QCOMPARE(PointF(10, 0), fromPolar<PointF>(10, 0));
  QCOMPARE(PointF(0, 20), fromPolar<PointF>(20, PI / 2));
  QCOMPARE(PointF(30 * std::sqrt(2), 30 * std::sqrt(2)), fromPolar<PointF>(60, PI / 4.0));

  QCOMPARE(PointF(10, 0), PointF::fromPolar(10, 0));
  QCOMPARE(PointF(0, 20), PointF::fromPolar(20, PI / 2));
  QCOMPARE(PointF(30 * std::sqrt(2), 30 * std::sqrt(2)), PointF::fromPolar(60, PI / 4.0));
}

void TestGeometry::test_2D_dot_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  Point ia(3, -4), ib(-2, 5);
  QCOMPARE(dot(ia, ib), QPoint::dotProduct(ia.toQPoint(), ib.toQPoint()));

  PointF fa1(23, 5224), fb1(-345, 21);
  QCOMPARE(dot(fa1, fb1), QPointF::dotProduct(fa1.toQPointF(), fb1.toQPointF()));

  PointF fa2(-213, 342.1), fb2(6354.23, 34.2);
  QCOMPARE(dot(fa2, fb2), QPointF::dotProduct(fa2.toQPointF(), fb2.toQPointF()));

  PointF fa3(1.12, 63.72), fb3(762.34, 123.2);
  QCOMPARE(dot(fa3, fb3), QPointF::dotProduct(fa3.toQPointF(), fb3.toQPointF()));

  //

  QCOMPARE(ia.dot(ib), QPoint::dotProduct(ia.toQPoint(), ib.toQPoint()));

  QCOMPARE(fa1.dot(fb1), QPointF::dotProduct(fa1.toQPointF(), fb1.toQPointF()));

  QCOMPARE(fa2.dot(fb2), QPointF::dotProduct(fa2.toQPointF(), fb2.toQPointF()));

  QCOMPARE(fa3.dot(fb3), QPointF::dotProduct(fa3.toQPointF(), fb3.toQPointF()));
}

void TestGeometry::test_2D_cross_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  Point ia(5, 7), ib(13, 17);
  QCOMPARE(cross(ia, ib), -6);

  PointF fa(1, 0), fb(0, 1);
  QVERIFY(cross(fa, fb) > 0);
  QVERIFY(cross(fb, fa) < 0);

  //

  QCOMPARE(ia.cross(ib), -6);

  QVERIFY(fa.cross(fb) > 0);
  QVERIFY(fb.cross(fa) < 0);
}

void TestGeometry::test_2D_distanceSquared_whenGivenFourNumbers_shouldWork() {
  using namespace Geometry2D;

  int px = 0, py = 0;
  int qx = 3, qy = 4;
  QCOMPARE(distanceSquared(px, py, qx, qy), 25);

  double pfx = 0, pfy = 0;
  double qfx = 6, qfy = 8;
  QCOMPARE(distanceSquared(pfx, pfy, qfx, qfy), 100);
}

void TestGeometry::test_2D_distanceSquared_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  Point p(0, 0);
  Point q(3, 4);
  QCOMPARE(distanceSquared(p, q), 25);

  PointF pf(0, 0);
  PointF qf(6, 8);
  QCOMPARE(distanceSquared(pf, qf), 100);

  //

  QCOMPARE(p.distSquaredTo(q), 25);
  QCOMPARE(pf.distSquaredTo(qf), 100);
}

void TestGeometry::test_2D_distance_whenGivenFourNumbers_shouldWork() {
  using namespace Geometry2D;

  int px = 0, py = 0;
  int qx = 3, qy = 4;
  QCOMPARE(distance(px, py, qx, qy), 5);

  double pfx = 0, pfy = 0;
  double qfx = 6, qfy = 8;
  QCOMPARE(distance(pfx, pfy, qfx, qfy), 10);
}

void TestGeometry::test_2D_distance_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  Point p(0, 0);
  Point q(3, 4);
  QCOMPARE(distance(p, q), 5);

  PointF pf(0, 0);
  PointF qf(6, 8);
  QCOMPARE(distance(pf, qf), 10);

  //

  QCOMPARE(p.distTo(q), 5);
  QCOMPARE(pf.distTo(qf), 10);
}

void TestGeometry::test_2D_rotateCW90_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    Point ipt(1, 0);
    for (Point rotation : {Point(1, 0), Point(0, -1), Point(-1, 0), Point(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCW90(ipt);
    }
  }
  /* floating point points. */ {
    PointF ipt(1, 0);
    for (PointF rotation : {PointF(1, 0), PointF(0, -1), PointF(-1, 0), PointF(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCW90<PointF>(ipt);
    }
  }

  /* integer points. */ {
    Point ipt(1, 0);
    for (Point rotation : {Point(1, 0), Point(0, -1), Point(-1, 0), Point(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt.rotateCW90();
    }
  }
  /* floating point points. */ {
    PointF ipt(1, 0);
    for (PointF rotation : {PointF(1, 0), PointF(0, -1), PointF(-1, 0), PointF(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt.rotateCW90();
    }
  }
}

void TestGeometry::test_2D_rotateCCW90_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    Point ipt(0, 1);
    for (Point rotation : {Point(0, 1), Point(-1, 0), Point(0, -1), Point(1, 0)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCCW90<Point>(ipt);
    }
  }
  /* floating point points. */ {
    PointF fpt(0, 1);
    for (PointF rotation : {PointF(0, 1), PointF(-1, 0), PointF(0, -1), PointF(1, 0)}) {
      QCOMPARE(fpt, rotation);
      fpt = rotateCCW90(fpt);
    }
  }

  /* integer points. */ {
    Point ipt(0, 1);
    for (Point rotation : {Point(0, 1), Point(-1, 0), Point(0, -1), Point(1, 0)}) {
      QCOMPARE(ipt, rotation);
      ipt.rotateCCW90();
    }
  }
  /* floating point points. */ {
    PointF fpt(0, 1);
    for (PointF rotation : {PointF(0, 1), PointF(-1, 0), PointF(0, -1), PointF(1, 0)}) {
      QCOMPARE(fpt, rotation);
      fpt.rotateCCW90();
    }
  }
}

void TestGeometry::test_2D_rotateCW_whenGivenAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;

  PointF pt(1, 0);
  QCOMPARE(rotateCW(pt, PI), PointF(-1, 0));
  QCOMPARE(rotateCW(pt, PI / 2.0), PointF(0, -1));
  QCOMPARE(rotateCW(pt, PI / 4.0), PointF(std::sqrt(2) / 2.0, -std::sqrt(2) / 2.0));

  //

  QCOMPARE(pt.rotatedCW(PI), PointF(-1, 0));
  QCOMPARE(pt.rotatedCW(PI / 2.0), PointF(0, -1));
  QCOMPARE(pt.rotatedCW(PI / 4.0), PointF(std::sqrt(2) / 2.0, -std::sqrt(2) / 2.0));
}

void TestGeometry::test_2D_rotateCCW_whenGivenAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;

  PointF pt(1, 0);
  QCOMPARE(rotateCCW(pt, PI), PointF(-1, 0));
  QCOMPARE(rotateCCW(pt, PI / 2.0), PointF(0, 1));
  QCOMPARE(rotateCCW(pt, PI / 4.0), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  //

  QCOMPARE(pt.rotatedCCW(PI), PointF(-1, 0));
  QCOMPARE(pt.rotatedCCW(PI / 2.0), PointF(0, 1));
  QCOMPARE(pt.rotatedCCW(PI / 4.0), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
}

void TestGeometry::test_2D_angle_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(angle(PointF(1, 0)), 0);
  QCOMPARE(angle(PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0)), PI / 4.0);
  QCOMPARE(angle(PointF(0, 1)), PI / 2.0);

  //

  QCOMPARE(PointF(1, 0).angle(), 0);
  QCOMPARE(PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0).angle(), PI / 4.0);
  QCOMPARE(PointF(0, 1).angle(), PI / 2.0);
}

void TestGeometry::test_2D_angleBetween_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    Point a(1, 0);
    Point b(1, 1);
    Point c(0, 1);

    QCOMPARE(angleBetween(a, c), PI / 2.0);
    QCOMPARE(angleBetween(c, a), -PI / 2.0);
    QCOMPARE(angleBetween(a, b), PI / 4.0);
    QCOMPARE(angleBetween(b, c), PI / 4.0);
  }

  /* floating point points. */ {
    PointF a(1, 0);
    PointF b(1, 1);
    PointF c(0, 1);

    QCOMPARE(angleBetween(a, c), PI / 2.0);
    QCOMPARE(angleBetween(c, a), -PI / 2.0);
    QCOMPARE(angleBetween(a, b), PI / 4.0);
    QCOMPARE(angleBetween(b, c), PI / 4.0);
  }

  /* integer points. */ {
    Point a(1, 0);
    Point b(1, 1);
    Point c(0, 1);

    QCOMPARE(a.angleTo(c), PI / 2.0);
    QCOMPARE(c.angleTo(a), -PI / 2.0);
    QCOMPARE(a.angleTo(b), PI / 4.0);
    QCOMPARE(b.angleTo(c), PI / 4.0);
  }

  /* floating point points. */ {
    PointF a(1, 0);
    PointF b(1, 1);
    PointF c(0, 1);

    QCOMPARE(a.angleTo(c), PI / 2.0);
    QCOMPARE(c.angleTo(a), -PI / 2.0);
    QCOMPARE(a.angleTo(b), PI / 4.0);
    QCOMPARE(b.angleTo(c), PI / 4.0);
  }
}

void TestGeometry::test_2D_lengthSquared_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(lengthSquared(Point(40, 30)), 2500);
  QCOMPARE(lengthSquared(PointF(40.0, 30.0)), 2500.0);

  //

  QCOMPARE(Point(40, 30).lengthSquared(), 2500);
  QCOMPARE(PointF(40.0, 30.0).lengthSquared(), 2500.0);
}

void TestGeometry::test_2D_length_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(length(Point(40, 30)), 50);
  QCOMPARE(length(PointF(40.0, 30.0)), 50.0);

  //

  QCOMPARE(Point(40, 30).length(), 50);
  QCOMPARE(PointF(40.0, 30.0).length(), 50.0);
}

void TestGeometry::test_2D_norm_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(norm(Point(40, 30)), 50);
  QCOMPARE(norm(PointF(40.0, 30.0)), 50.0);

  //

  QCOMPARE(Point(40, 30).norm(), 50);
  QCOMPARE(PointF(40.0, 30.0).norm(), 50.0);
}

void TestGeometry::test_2D_manhattanLength_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(manhattanLength(Point(40, 30)), 70);
  QCOMPARE(manhattanLength(PointF(40, 30)), 70);

  //

  QCOMPARE(Point(40, 30).manhattanLength(), 70);
  QCOMPARE(PointF(40, 30).manhattanLength(), 70);
}

void TestGeometry::test_2D_unitaryAxisDirection_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(unitaryAxisDirection(Point(4, 3)), Point(1, 1));
  QCOMPARE(unitaryAxisDirection(PointF(5, 4)), PointF(1, 1));
  QCOMPARE(unitaryAxisDirection(Point(0, 0)), Point(0, 0));
  QCOMPARE(unitaryAxisDirection(PointF(0, 0)), PointF(0, 0));
  QCOMPARE(unitaryAxisDirection(Point(-10, 10)), Point(-1, 1));
  QCOMPARE(unitaryAxisDirection(PointF(5, -4)), PointF(1, -1));

  //

  QCOMPARE(Point(4, 3).unitaryAxisNormalized(), Point(1, 1));
  QCOMPARE(PointF(5, 4).unitaryAxisNormalized(), PointF(1, 1));
  QCOMPARE(Point(0, 0).unitaryAxisNormalized(), Point(0, 0));
  QCOMPARE(PointF(0, 0).unitaryAxisNormalized(), PointF(0, 0));
  QCOMPARE(Point(-10, 10).unitaryAxisNormalized(), Point(-1, 1));
  QCOMPARE(PointF(5, -4).unitaryAxisNormalized(), PointF(1, -1));
}

void TestGeometry::test_2D_resize_whenGivenAFloatingPointPointAndAFloatingPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(resize(PointF(2, 2), 1), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(resize(PointF(-10, -10), std::sqrt(2)), -PointF(1, 1));

  //

  QCOMPARE(PointF(2, 2).resized(1), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(PointF(-10, -10).resized(std::sqrt(2)), -PointF(1, 1));
}

void TestGeometry::test_2D_normalize_whenGivenAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(normalize(PointF(2, 2)), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(normalize(PointF(-10, -10)), -PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  //

  QCOMPARE(PointF(2, 2).normalized(), PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(PointF(-10, -10).normalized(), -PointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
}

void TestGeometry::test_2D_normalize_whenGivenAnIntegerPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(normalize(Point(2, 2)), Point(1, 1));
  QCOMPARE(normalize(Point(2, -2)), Point(1, -1));
  QCOMPARE(normalize(Point(-10, -10)), -Point(1, 1));
  QCOMPARE(normalize(Point(-8, 10)), Point(-4, 5));

  //

  QCOMPARE(Point(2, 2).normalized(), Point(1, 1));
  QCOMPARE(Point(2, -2).normalized(), Point(1, -1));
  QCOMPARE(Point(-10, -10).normalized(), -Point(1, 1));
  QCOMPARE(Point(-8, 10).normalized(), Point(-4, 5));
}

void TestGeometry::test_2D_isTriangle_whenGivenThreeNumbers_shouldWork() {
  using namespace Geometry2D;

  QVERIFY(isTriangle(7, 10, 5));
  QVERIFY(not isTriangle(1, 10, 12));
}

void TestGeometry::test_2D_signedArea2_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QVector<Point> poly1 = QVector<Point>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(signedArea2(poly1), -200);

  QVector<Point> rpoly1(QVector<Point>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(signedArea2(rpoly1), 200);

  QVector<PointF> poly2 =
      QVector<PointF>{PointF(3, 4), PointF(5, 11), PointF(12, 8), PointF(9, 5), PointF(5, 6)};
  QCOMPARE(signedArea2(poly2), -60.0);

  QVector<PointF> rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(signedArea2(rpoly2), 60.0);
}

void TestGeometry::test_2D_signedArea_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QVector<Point> poly1 = QVector<Point>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(signedArea(poly1), -100);

  QVector<Point> rpoly1(QVector<Point>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(signedArea(rpoly1), 100);

  QVector<PointF> poly2 =
      QVector<PointF>{PointF(3, 4), PointF(5, 11), PointF(12, 8), PointF(9, 5), PointF(5, 6)};
  QCOMPARE(signedArea(poly2), -30.0);

  QVector<PointF> rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(signedArea(rpoly2), 30.0);
}

void TestGeometry::test_2D_area2_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QVector<Point> poly1 = QVector<Point>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(area2(poly1), 200);

  QVector<Point> rpoly1(QVector<Point>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(area2(rpoly1), 200);

  QVector<PointF> poly2 =
      QVector<PointF>{PointF(3, 4), PointF(5, 11), PointF(12, 8), PointF(9, 5), PointF(5, 6)};
  QCOMPARE(area2(poly2), 60.0);

  QVector<PointF> rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(area2(rpoly2), 60.0);
}

void TestGeometry::test_2D_area_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QVector<Point> poly1 = QVector<Point>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(area(poly1), 100);

  QVector<Point> rpoly1(QVector<Point>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(area(rpoly1), 100);

  QVector<PointF> poly2 =
      QVector<PointF>{PointF(3, 4), PointF(5, 11), PointF(12, 8), PointF(9, 5), PointF(5, 6)};
  QCOMPARE(area(poly2), 30.0);

  QVector<PointF> rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(area(rpoly2), 30.0);
}

void TestGeometry::test_2D_centroid_whenGivenAPolygonOfFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  QVector<PointF> poly1{QVector<PointF>{PointF(1, 0), PointF(2, 0), PointF(0, 3)}};

  QCOMPARE(centroid(poly1), PointF(1, 1));

  QVector<PointF> poly2 =
      QVector<PointF>({PointF(1, 0), PointF(2, 1), PointF(0, 3), PointF(-1, 2), PointF(-2, -1)});
  QCOMPARE(centroid(poly2), PointF(-0.08 - 1.0 / 300.0, 0.91 + 2.0 / 300.0));
}

void TestGeometry::test_2D_projectPointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    PointF a(0, 0), b(2, 2), c(1, 0), d(0, 1);
    QCOMPARE(projectPointLine(a, b, c), PointF(0.5, 0.5));
    QCOMPARE(projectPointLine(a, b, d), PointF(0.5, 0.5));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(projectPointLine(a, b, c), PointF(1, 1));
  }

  //

  {
    PointF a(0, 0), b(2, 2), c(1, 0), d(0, 1);
    QCOMPARE(c.projectedOntoLine(a, b), PointF(0.5, 0.5));
    QCOMPARE(c.projectedOntoLine(a, b), PointF(0.5, 0.5));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(c.projectedOntoLine(a, b), PointF(1, 1));
  }
}

void TestGeometry::test_2D_distancePointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    PointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(distancePointLine(a, b, c), std::sqrt(2));
    QCOMPARE(distancePointLine(a, b, d), std::sqrt(2));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(distancePointLine(a, b, c), 0.0);
  }

  //

  {
    PointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(c.distToLine(a, b), std::sqrt(2));
    QCOMPARE(d.distToLine(a, b), std::sqrt(2));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(c.distToLine(a, b), 0.0);
  }
}

void TestGeometry::test_2D_reflectPointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    PointF a(0, 0), b(0, 1);
    PointF c(1, 0);
    PointF d(-1, 0);
    QCOMPARE(reflectPointLine(a, b, c), d);
    QCOMPARE(reflectPointLine(a, b, d), c);
  }

  {
    PointF a(1, 0), b(0, 0);
    PointF c(0, 1);
    PointF d(0, -1);
    QCOMPARE(reflectPointLine(a, b, c), d);
    QCOMPARE(reflectPointLine(a, b, d), c);
  }

  //

  {
    PointF a(0, 0), b(0, 1);
    PointF c(1, 0);
    PointF d(-1, 0);
    QCOMPARE(c.reflectedOntoLine(a, b), d);
    QCOMPARE(d.reflectedOntoLine(a, b), c);
  }

  {
    PointF a(1, 0), b(0, 0);
    PointF c(0, 1);
    PointF d(0, -1);
    QCOMPARE(c.reflectedOntoLine(a, b), d);
    QCOMPARE(d.reflectedOntoLine(a, b), c);
  }
}

void TestGeometry::test_2D_isOnTheLeft_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  PointF a(0, 0), b(0, 10), c(-5, 5);
  QVERIFY(isOnTheLeft(a, b, c));
  QVERIFY(isOnTheLeft(a, b, c));
  QVERIFY(!isOnTheLeft(a, b, -c));
  QVERIFY(isOnTheLeft(b, a, -c));

  //

  QVERIFY(c.isOnTheLeftOf(a, b));
  QVERIFY(c.isOnTheLeftOf(a, b));
  QVERIFY(!(-c).isOnTheLeftOf(a, b));
  QVERIFY((-c).isOnTheLeftOf(b, a));
}

void TestGeometry::test_2D_isOnTheRight_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  PointF a(0, 0), b(0, 10), c(-5, 5);
  QVERIFY(!c.isOnTheRightOf(a, b));
  QVERIFY(!c.isOnTheRightOf(a, b));
  QVERIFY((-c).isOnTheRightOf(a, b));
  QVERIFY(!(-c).isOnTheRightOf(b, a));
}

void TestGeometry::test_2D_projectPointSegment_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  QCOMPARE(projectPointSegment(PointF(-5, -2), PointF(10, 4), PointF(3, 7)), PointF(5, 2));
  QCOMPARE(projectPointSegment(PointF(7.5, 3), PointF(10, 4), PointF(3, 7)), PointF(7.5, 3));
  QCOMPARE(projectPointSegment(PointF(-5, -2), PointF(2.5, 1), PointF(3, 7)), PointF(2.5, 1));

  //

  QCOMPARE(PointF(3, 7).projectedOntoSegment(PointF(-5, -2), PointF(10, 4)), PointF(5, 2));
  QCOMPARE(PointF(3, 7).projectedOntoSegment(PointF(7.5, 3), PointF(10, 4)), PointF(7.5, 3));
  QCOMPARE(PointF(3, 7).projectedOntoSegment(PointF(-5, -2), PointF(2.5, 1)), PointF(2.5, 1));
}

void TestGeometry::test_2D_distancePointSegment_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    PointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(distancePointSegment(a, b, c), std::sqrt(2));
    QCOMPARE(distancePointSegment(a, b, d), std::sqrt(2));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(distancePointSegment(a, b, c), 0.0);
  }

  //

  {
    PointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(c.distToSegment(a, b), std::sqrt(2));
    QCOMPARE(d.distToSegment(a, b), std::sqrt(2));
  }

  {
    PointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(c.distToSegment(a, b), 0.0);
  }
}

void TestGeometry::test_2D_linesParallel_whenGivenFourPoints_shouldWork() {
  using namespace Geometry2D;
  /* integer points. */ {
    QVERIFY(linesParallel(Point(1, 1), Point(3, 5), Point(2, 1), Point(4, 5)));
    QVERIFY(!linesParallel(Point(1, 1), Point(3, 5), Point(2, 0), Point(4, 5)));
    QVERIFY(linesParallel(Point(1, 1), Point(3, 5), Point(5, 9), Point(7, 13)));
  }
  /* floating point points. */ {
    QVERIFY(linesParallel(PointF(1, 1), PointF(3, 5), PointF(2, 1), PointF(4, 5)));
    QVERIFY(!linesParallel(PointF(1, 1), PointF(3, 5), PointF(2, 0), PointF(4, 5)));
    QVERIFY(linesParallel(PointF(1, 1), PointF(3, 5), PointF(5, 9), PointF(7, 13)));
  }
}

void TestGeometry::test_2D_linesCollinear_whenGivenFourPoints_shouldWork() {
  using namespace Geometry2D;
  /* integer points. */ {
    QVERIFY(!linesCollinear(Point(1, 1), Point(3, 5), Point(2, 1), Point(4, 5)));
    QVERIFY(!linesCollinear(Point(1, 1), Point(3, 5), Point(2, 0), Point(4, 5)));
    QVERIFY(linesCollinear(Point(1, 1), Point(3, 5), Point(5, 9), Point(7, 13)));
  }
  /* floating point points. */ {
    QVERIFY(!linesCollinear(PointF(1, 1) / 2.0,
                            PointF(3, 5) / 2.0,
                            PointF(2, 1) / 2.0,
                            PointF(4, 5) / 2.0));
    QVERIFY(!linesCollinear(PointF(1, 1) / 2.0,
                            PointF(3, 5) / 2.0,
                            PointF(2, 0) / 2.0,
                            PointF(4, 5) / 2.0));
    QVERIFY(linesCollinear(PointF(1, 1) / 2.0,
                           PointF(3, 5) / 2.0,
                           PointF(5, 9) / 2.0,
                           PointF(7, 13) / 2.0));
  }
}

void TestGeometry::test_2D_segmentsIntersect_whenGivenFourFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;

  QVERIFY(segmentsIntersect(PointF(0, 0), PointF(2, 4), PointF(3, 1), PointF(-1, 3)));
  QVERIFY(segmentsIntersect(PointF(0, 0), PointF(2, 4), PointF(4, 3), PointF(0, 5)));
  QVERIFY(segmentsIntersect(PointF(0, 0), PointF(2, 4), PointF(2, -1), PointF(-2, 1)));
  QVERIFY(!segmentsIntersect(PointF(0, 0), PointF(2, 4), PointF(5, 5), PointF(1, 7)));
}

void TestGeometry::test_2D_linesIntersection_whenGivenFourFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;

  /* x and y axis */ {
    auto intersection = linesIntersection(PointF(0, 2), PointF(0, 4), PointF(2, 0), PointF(100, 0));
    QVERIFY(intersection);
    QCOMPARE(intersection.value(), PointF(0, 0));
  }
  /* collinear */ {
    auto intersection = linesIntersection(PointF(0, 0), PointF(1, 1), PointF(2, 2), PointF(3, 3));
    QVERIFY(!intersection);
  }
  /* parallel */ {
    auto intersection = linesIntersection(PointF(0, 1), PointF(1, 2), PointF(2, 2), PointF(3, 3));
    QVERIFY(!intersection);
  }
  /* any case */ {
    auto intersection =
        linesIntersection(PointF(0, -5), PointF(0, 0), PointF(-4.5, -4.5), PointF(3, -7));
    QVERIFY(intersection);
    QCOMPARE(intersection.value(), PointF(0, -6));
  }
  /* any case */ {
    auto intersection =
        linesIntersection(PointF(0, 6), PointF(-9, -2), PointF(-2, -0), PointF(0, 0));
    QVERIFY(intersection);
    QCOMPARE(intersection.value(), PointF(-6.75, 0));
  }
}

void TestGeometry::test_2D_segmentsIntersection_whenGivenFourFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;

  /* x and y axis */ {
    auto intersection =
        segmentsIntersection(PointF(0, 2), PointF(0, 4), PointF(2, 0), PointF(100, 0));
    QVERIFY(!intersection);
  }
  /* collinear */ {
    auto intersection =
        segmentsIntersection(PointF(0, 0), PointF(1, 1), PointF(2, 2), PointF(3, 3));
    QVERIFY(!intersection);
  }
  /* parallel */ {
    auto intersection =
        segmentsIntersection(PointF(0, 1), PointF(1, 2), PointF(2, 2), PointF(3, 3));
    QVERIFY(!intersection);
  }
  /* any case */ {
    auto intersection =
        segmentsIntersection(PointF(0, -5), PointF(0, 0), PointF(-4.5, -4.5), PointF(3, -7));
    QVERIFY(!intersection);
  }
  /* any case */ {
    auto intersection =
        segmentsIntersection(PointF(0, -10), PointF(0, 0), PointF(-4.5, -4.5), PointF(3, -7));
    QVERIFY(intersection);
    QCOMPARE(intersection.value(), PointF(0, -6));
  }
  /* any case */ {
    auto intersection =
        segmentsIntersection(PointF(0, 6), PointF(-9, -2), PointF(-2, 0), PointF(0, 0));
    QVERIFY(!intersection);
  }
}

void TestGeometry::test_2D_convexHull_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;
  /* poly of integer points */ {
    QVector<Point> poly;
    poly << Point(30, 60) << Point(50, 40) << Point(0, 30) << Point(15, 25) << Point(70, 30)
         << Point(55, 20) << Point(50, 10) << Point(20, 0);
    QCOMPARE(
        convexHull(poly),
        QVector<Point>({Point(0, 30), Point(20, 0), Point(50, 10), Point(70, 30), Point(30, 60)}));
  }
  /* poly of floating point points */ {
    QVector<PointF> poly({PointF(-7, 8),
                          PointF(-4, 6),
                          PointF(2, 6),
                          PointF(6, 4),
                          PointF(8, 6),
                          PointF(7, -2),
                          PointF(4, -6),
                          PointF(8, -7),
                          PointF(0, 0),
                          PointF(3, -2),
                          PointF(6, -10),
                          PointF(0, -6),
                          PointF(-9, -5),
                          PointF(-8, -2),
                          PointF(-8, 0),
                          PointF(-10, 3),
                          PointF(-2, 2),
                          PointF(-10, 4)});
    QCOMPARE(convexHull(poly),
             QVector<PointF>({PointF(-10, 3),
                              PointF(-9, -5),
                              PointF(6, -10),
                              PointF(8, -7),
                              PointF(8, 6),
                              PointF(-7, 8),
                              PointF(-10, 4)}));
  }
}

void TestGeometry::test_2D_pointInPolygon_whenGivenAPolygonAndAPoint_shouldWork() {
  using namespace Geometry2D;
  QVector<PointF> poly;
  poly += (PointF(0, 0));
  poly << (PointF(5, 0));
  poly.push_back(PointF(5, 5));
  poly.append(PointF(0, 5));

  QVERIFY(pointInPolygon(poly, PointF(2, 2)));
  QVERIFY(pointInPolygon(poly, PointF(2, 0)));
  QVERIFY(pointInPolygon(poly, PointF(0, 2)));
  QVERIFY(!pointInPolygon(poly, PointF(5, 2)));
  QVERIFY(!pointInPolygon(poly, PointF(2, 5)));

  //

  QVERIFY(PointF(2, 2).isInPolygon(poly));
  QVERIFY(PointF(2, 0).isInPolygon(poly));
  QVERIFY(PointF(0, 2).isInPolygon(poly));
  QVERIFY(!PointF(5, 2).isInPolygon(poly));
  QVERIFY(!PointF(2, 5).isInPolygon(poly));
}

void TestGeometry::test_2D_pointOnPolygon_whenGivenAPolygonAndAPoint_shouldWork() {
  using namespace Geometry2D;
  QVector<PointF> poly;
  poly += (PointF(0, 0));
  poly << (PointF(5, 0));
  poly.push_back(PointF(5, 5));
  poly.append(PointF(0, 5));

  QVERIFY(!pointOnPolygon(poly, PointF(2, 2)));
  QVERIFY(pointOnPolygon(poly, PointF(2, 0)));
  QVERIFY(pointOnPolygon(poly, PointF(0, 2)));
  QVERIFY(pointOnPolygon(poly, PointF(5, 2)));
  QVERIFY(pointOnPolygon(poly, PointF(2, 5)));

  //

  QVERIFY(!PointF(2, 2).isOnPolygon(poly));
  QVERIFY(PointF(2, 0).isOnPolygon(poly));
  QVERIFY(PointF(0, 2).isOnPolygon(poly));
  QVERIFY(PointF(5, 2).isOnPolygon(poly));
  QVERIFY(PointF(2, 5).isOnPolygon(poly));
}

QTEST_MAIN(TestGeometry)
