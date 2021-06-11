#include "TestGeometry.h"

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

void TestGeometry::test_2D_operatorLess_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    QPoint iLhsEq(10, 10);
    QPoint iRhsEq(10, 10);
    QCOMPARE(iLhsEq < iRhsEq, false);

    QPoint iLhsLessX(5, 10);
    QPoint iRhsLessX(10, 10);
    QCOMPARE(iLhsLessX < iRhsLessX, true);

    QPoint iLhsLessY(10, 5);
    QPoint iRhsLessY(10, 10);
    QCOMPARE(iLhsLessY < iRhsLessY, true);
  }

  /* floating point points. */ {
    QPointF fLhsEq(10, 10);
    QPointF fRhsEq(10, 10);
    QCOMPARE(fLhsEq < fRhsEq, false);

    QPointF fLhsLessX(5, 10);
    QPointF fRhsLessX(10, 10);
    QCOMPARE(fLhsLessX < fRhsLessX, true);

    QPointF fLhsLessY(10, 5);
    QPointF fRhsLessY(10, 10);
    QCOMPARE(fLhsLessY < fRhsLessY, true);
  }
}

void TestGeometry::test_2D_dot_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  QPoint ia(3, -4), ib(-2, 5);
  QCOMPARE(dot(ia, ib), QPoint::dotProduct(ia, ib));

  QPointF fa1(23, 5224), fb1(-345, 21);
  QCOMPARE(dot(fa1, fb1), QPointF::dotProduct(fa1, fb1));

  QPointF fa2(-213, 342.1), fb2(6354.23, 34.2);
  QCOMPARE(dot(fa2, fb2), QPointF::dotProduct(fa2, fb2));

  QPointF fa3(1.12, 63.72), fb3(762.34, 123.2);
  QCOMPARE(dot(fa3, fb3), QPointF::dotProduct(fa3, fb3));
}

void TestGeometry::test_2D_cross_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  QPoint ia(5, 7), ib(13, 17);
  QCOMPARE(cross(ia, ib), -6);

  QPointF fa(1, 0), fb(0, 1);
  QVERIFY(cross(fa, fb) > 0);
  QVERIFY(cross(fb, fa) < 0);
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

  QPoint p(0, 0);
  QPoint q(3, 4);
  QCOMPARE(distanceSquared(p, q), 25);

  QPointF pf(0, 0);
  QPointF qf(6, 8);
  QCOMPARE(distanceSquared(pf, qf), 100);
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

  QPoint p(0, 0);
  QPoint q(3, 4);
  QCOMPARE(distance(p, q), 5);

  QPointF pf(0, 0);
  QPointF qf(6, 8);
  QCOMPARE(distance(pf, qf), 10);
}

void TestGeometry::test_2D_rotateCW90_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    QPoint ipt(1, 0);
    for (QPoint rotation : {QPoint(1, 0), QPoint(0, -1), QPoint(-1, 0), QPoint(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCW90(ipt);
    }
  }
  /* floating point points. */ {
    QPointF ipt(1, 0);
    for (QPointF rotation : {QPointF(1, 0), QPointF(0, -1), QPointF(-1, 0), QPointF(0, 1)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCW90<QPointF>(ipt);
    }
  }
}

void TestGeometry::test_2D_rotateCCW90_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    QPoint ipt(0, 1);
    for (QPoint rotation : {QPoint(0, 1), QPoint(-1, 0), QPoint(0, -1), QPoint(1, 0)}) {
      QCOMPARE(ipt, rotation);
      ipt = rotateCCW90<QPoint>(ipt);
    }
  }
  /* floating point points. */ {
    QPointF fpt(0, 1);
    for (QPointF rotation : {QPointF(0, 1), QPointF(-1, 0), QPointF(0, -1), QPointF(1, 0)}) {
      QCOMPARE(fpt, rotation);
      fpt = rotateCCW90(fpt);
    }
  }
}

void TestGeometry::test_2D_rotateCCW_whenGivenAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;

  QPointF pt(1, 0);
  QCOMPARE(rotateCCW(pt, PI), QPointF(-1, 0));
  QCOMPARE(rotateCCW(pt, PI / 2.0), QPointF(0, 1));
  QCOMPARE(rotateCCW(pt, PI / 4.0), QPointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
}

void TestGeometry::test_2D_angle_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(angle(QPointF(1, 0)), 0);
  QCOMPARE(angle(QPointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0)), PI / 4.0);
  QCOMPARE(angle(QPointF(0, 1)), PI / 2.0);
}

void TestGeometry::test_2D_angleBetween_whenGivenTwoPoints_shouldWork() {
  using namespace Geometry2D;

  /* integer points. */ {
    QPoint a(1, 0);
    QPoint b(1, 1);
    QPoint c(0, 1);

    QCOMPARE(angleBetween(a, c), PI / 2.0);
    QCOMPARE(angleBetween(c, a), -PI / 2.0);
    QCOMPARE(angleBetween(a, b), PI / 4.0);
    QCOMPARE(angleBetween(b, c), PI / 4.0);
  }

  /* floating point points. */ {
    QPointF a(1, 0);
    QPointF b(1, 1);
    QPointF c(0, 1);

    QCOMPARE(angleBetween(a, c), PI / 2.0);
    QCOMPARE(angleBetween(c, a), -PI / 2.0);
    QCOMPARE(angleBetween(a, b), PI / 4.0);
    QCOMPARE(angleBetween(b, c), PI / 4.0);
  }
}

void TestGeometry::test_2D_lengthSquared_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(lengthSquared(QPoint(40, 30)), 2500);
  QCOMPARE(lengthSquared(QPointF(40.0, 30.0)), 2500.0);
}

void TestGeometry::test_2D_length_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(length(QPoint(40, 30)), 50);
  QCOMPARE(length(QPointF(40.0, 30.0)), 50.0);
}

void TestGeometry::test_2D_manhattanLength_whenGivenAPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(manhattanLength(QPoint(40, 30)), 70);
  QCOMPARE(manhattanLength(QPointF(40, 30)), 70);
}

void TestGeometry::test_2D_resize_whenGivenAFloatingPointPointAndAFloatingPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(resize(QPointF(2, 2), 1), QPointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(resize(QPointF(-10, -10), std::sqrt(2)), -QPointF(1, 1));
}

void TestGeometry::test_2D_normalize_whenGivenAFloatingPointPointAndAFloatingPoint_shouldWork() {
  using namespace Geometry2D;

  QCOMPARE(normalize(QPointF(2, 2)), QPointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));

  QCOMPARE(normalize(QPointF(-10, -10)), -QPointF(std::sqrt(2) / 2.0, std::sqrt(2) / 2.0));
}

void TestGeometry::test_2D_isTriangle_whenGivenThreeNumbers_shouldWork() {
  using namespace Geometry2D;

  QVERIFY(isTriangle(7, 10, 5));
  QVERIFY(not isTriangle(1, 10, 12));
}

void TestGeometry::test_2D_signedArea2_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QPolygon poly1 = QVector<QPoint>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(signedArea2(poly1), -200);

  QPolygon rpoly1(QVector<QPoint>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(signedArea2(rpoly1), 200);

  QPolygonF poly2 =
      QVector{QPointF(3, 4), QPointF(5, 11), QPointF(12, 8), QPointF(9, 5), QPointF(5, 6)};
  QCOMPARE(signedArea2(poly2), -60.0);

  QPolygonF rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(signedArea2(rpoly2), 60.0);
}

void TestGeometry::test_2D_signedArea_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QPolygon poly1 = QVector<QPoint>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(signedArea(poly1), -100);

  QPolygon rpoly1(QVector<QPoint>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(signedArea(rpoly1), 100);

  QPolygonF poly2 =
      QVector{QPointF(3, 4), QPointF(5, 11), QPointF(12, 8), QPointF(9, 5), QPointF(5, 6)};
  QCOMPARE(signedArea(poly2), -30.0);

  QPolygonF rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(signedArea(rpoly2), 30.0);
}

void TestGeometry::test_2D_area2_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QPolygon poly1 = QVector<QPoint>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(area2(poly1), 200);

  QPolygon rpoly1(QVector<QPoint>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(area2(rpoly1), 200);

  QPolygonF poly2 =
      QVector{QPointF(3, 4), QPointF(5, 11), QPointF(12, 8), QPointF(9, 5), QPointF(5, 6)};
  QCOMPARE(area2(poly2), 60.0);

  QPolygonF rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(area2(rpoly2), 60.0);
}

void TestGeometry::test_2D_area_whenGivenAPolygon_shouldWork() {
  using namespace Geometry2D;

  QPolygon poly1 = QVector<QPoint>{{0, 0}, {0, 10}, {10, 10}, {10, 0}};
  QCOMPARE(area(poly1), 100);

  QPolygon rpoly1(QVector<QPoint>(poly1.rbegin(), poly1.rend()));
  QCOMPARE(area(rpoly1), 100);

  QPolygonF poly2 =
      QVector{QPointF(3, 4), QPointF(5, 11), QPointF(12, 8), QPointF(9, 5), QPointF(5, 6)};
  QCOMPARE(area(poly2), 30.0);

  QPolygonF rpoly2(poly2);
  std::reverse(rpoly2.begin(), rpoly2.end());
  QCOMPARE(area(rpoly2), 30.0);
}

void TestGeometry::test_2D_centroid_whenGivenAPolygonOfFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  QPolygonF poly1{QVector{QPointF(1, 0), QPointF(2, 0), QPointF(0, 3)}};

  QCOMPARE(centroid(poly1), QPointF(1, 1));

  QPolygonF poly2 =
      QVector({QPointF(1, 0), QPointF(2, 1), QPointF(0, 3), QPointF(-1, 2), QPointF(-2, -1)});
  QCOMPARE(centroid(poly2), QPointF(-0.08 - 1.0 / 300.0, 0.91 + 2.0 / 300.0));
}

void TestGeometry::test_2D_projectPointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    QPointF a(0, 0), b(2, 2), c(1, 0), d(0, 1);
    QCOMPARE(projectPointLine(a, b, c), QPointF(0.5, 0.5));
    QCOMPARE(projectPointLine(a, b, d), QPointF(0.5, 0.5));
  }

  {
    QPointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(projectPointLine(a, b, c), QPointF(1, 1));
  }
}

void TestGeometry::test_2D_projectPointLine_whenGivenALineAndAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;
  {
    QLineF line(0, 0, 2, 2);
    QPointF c(1, 0), d(0, 1);
    QCOMPARE(projectPointLine(line, c), QPointF(0.5, 0.5));
    QCOMPARE(projectPointLine(line, d), QPointF(0.5, 0.5));
  }

  {
    QLineF line(0, 0, 2, 2);
    QPointF c(1, 1);
    QCOMPARE(projectPointLine(line, c), QPointF(1, 1));
  }
}

void TestGeometry::test_2D_distancePointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    QPointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(distancePointLine(a, b, c), std::sqrt(2));
    QCOMPARE(distancePointLine(a, b, d), std::sqrt(2));
  }

  {
    QPointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(distancePointLine(a, b, c), 0.0);
  }
}

void TestGeometry::test_2D_distancePointLine_whenGivenALineAndAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;
  {
    QLineF line(0, 0, 2, 2);
    QPointF c(2, 0), d(0, 2);
    QCOMPARE(distancePointLine(line, c), std::sqrt(2));
    QCOMPARE(distancePointLine(line, d), std::sqrt(2));
  }

  {
    QLineF line(0, 0, 2, 2);
    QPointF c(1, 1);
    QCOMPARE(distancePointLine(line, c), 0.0);
  }
}

void TestGeometry::test_2D_reflectPointLine_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    QPointF a(0, 0), b(0, 1);
    QPointF c(1, 0);
    QPointF d(-1, 0);
    QCOMPARE(reflectPointLine(a, b, c), d);
    QCOMPARE(reflectPointLine(a, b, d), c);
  }

  {
    QPointF a(1, 0), b(0, 0);
    QPointF c(0, 1);
    QPointF d(0, -1);
    QCOMPARE(reflectPointLine(a, b, c), d);
    QCOMPARE(reflectPointLine(a, b, d), c);
  }
}

void TestGeometry::test_2D_reflectPointLine_whenGivenALineAndAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;
  {
    QLineF line(0, 0, 0, 1);
    QPointF c(1, 0);
    QPointF d(-1, 0);
    QCOMPARE(reflectPointLine(line, c), d);
    QCOMPARE(reflectPointLine(line, d), c);
  }

  {
    QLineF line(1, 0, 0, 0);
    QPointF c(0, 1);
    QPointF d(0, -1);
    QCOMPARE(reflectPointLine(line, c), d);
    QCOMPARE(reflectPointLine(line, d), c);
  }
}

void TestGeometry::test_2D_projectPointSegment_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  QCOMPARE(projectPointSegment(QPointF(-5, -2), QPointF(10, 4), QPointF(3, 7)), QPointF(5, 2));
  QCOMPARE(projectPointSegment(QPointF(7.5, 3), QPointF(10, 4), QPointF(3, 7)), QPointF(7.5, 3));
  QCOMPARE(projectPointSegment(QPointF(-5, -2), QPointF(2.5, 1), QPointF(3, 7)), QPointF(2.5, 1));
}

void TestGeometry::test_2D_projectPointSegment_whenGivenALineAndAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;
  QCOMPARE(projectPointSegment(QLineF(-5, -2, 10, 4), QPointF(3, 7)), QPointF(5, 2));
  QCOMPARE(projectPointSegment(QLineF(7.5, 3, 10, 4), QPointF(3, 7)), QPointF(7.5, 3));
  QCOMPARE(projectPointSegment(QLineF(-5, -2, 2.5, 1), QPointF(3, 7)), QPointF(2.5, 1));
}

void TestGeometry::test_2D_distancePointSegment_whenGivenThreeFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;
  {
    QPointF a(0, 0), b(2, 2), c(2, 0), d(0, 2);
    QCOMPARE(distancePointSegment(a, b, c), std::sqrt(2));
    QCOMPARE(distancePointSegment(a, b, d), std::sqrt(2));
  }

  {
    QPointF a(0, 0), b(2, 2), c(1, 1);
    QCOMPARE(distancePointSegment(a, b, c), 0.0);
  }
}

void TestGeometry::test_2D_distancePointSegment_whenGivenALineAndAFloatingPointPoint_shouldWork() {
  using namespace Geometry2D;
  {
    QLineF line(0, 0, 2, 2);
    QPointF c(2, 0), d(0, 2);
    QCOMPARE(distancePointSegment(line, c), std::sqrt(2));
    QCOMPARE(distancePointSegment(line, d), std::sqrt(2));
  }

  {
    QLineF line(0, 0, 2, 2);
    QPointF c(1, 1);
    QCOMPARE(distancePointSegment(line, c), 0.0);
  }
}

void TestGeometry::test_2D_linesParallel_whenGivenFourPoints_shouldWork() {
  using namespace Geometry2D;
  /* integer points. */ {
    QVERIFY(linesParallel(QPoint(1, 1), QPoint(3, 5), QPoint(2, 1), QPoint(4, 5)));
    QVERIFY(!linesParallel(QPoint(1, 1), QPoint(3, 5), QPoint(2, 0), QPoint(4, 5)));
    QVERIFY(linesParallel(QPoint(1, 1), QPoint(3, 5), QPoint(5, 9), QPoint(7, 13)));
  }
  /* floating point points. */ {
    QVERIFY(linesParallel(QPointF(1, 1), QPointF(3, 5), QPointF(2, 1), QPointF(4, 5)));
    QVERIFY(!linesParallel(QPointF(1, 1), QPointF(3, 5), QPointF(2, 0), QPointF(4, 5)));
    QVERIFY(linesParallel(QPointF(1, 1), QPointF(3, 5), QPointF(5, 9), QPointF(7, 13)));
  }
}

void TestGeometry::test_2D_linesParallel_whenGivenTwoLines_shouldWork() {
  using namespace Geometry2D;
  QVERIFY(linesParallel(QLineF(1, 1, 3, 5), QLineF(2, 1, 4, 5)));
  QVERIFY(!linesParallel(QLineF(1, 1, 3, 5), QLineF(2, 0, 4, 5)));
  QVERIFY(linesParallel(QLineF(1, 1, 3, 5), QLineF(5, 9, 7, 13)));
}

void TestGeometry::test_2D_linesCollinear_whenGivenFourPoints_shouldWork() {
  using namespace Geometry2D;
  /* integer points. */ {
    QVERIFY(!linesCollinear(QPoint(1, 1), QPoint(3, 5), QPoint(2, 1), QPoint(4, 5)));
    QVERIFY(!linesCollinear(QPoint(1, 1), QPoint(3, 5), QPoint(2, 0), QPoint(4, 5)));
    QVERIFY(linesCollinear(QPoint(1, 1), QPoint(3, 5), QPoint(5, 9), QPoint(7, 13)));
  }
  /* floating point points. */ {
    QVERIFY(!linesCollinear(QPointF(1, 1) / 2.0,
                            QPointF(3, 5) / 2.0,
                            QPointF(2, 1) / 2.0,
                            QPointF(4, 5) / 2.0));
    QVERIFY(!linesCollinear(QPointF(1, 1) / 2.0,
                            QPointF(3, 5) / 2.0,
                            QPointF(2, 0) / 2.0,
                            QPointF(4, 5) / 2.0));
    QVERIFY(linesCollinear(QPointF(1, 1) / 2.0,
                           QPointF(3, 5) / 2.0,
                           QPointF(5, 9) / 2.0,
                           QPointF(7, 13) / 2.0));
  }
}

void TestGeometry::test_2D_linesCollinear_whenGivenTwoLines_shouldWork() {
  using namespace Geometry2D;
  QVERIFY(!linesCollinear(QLineF(1, 1, 3, 5), QLineF(2, 1, 4, 5)));
  QVERIFY(!linesCollinear(QLineF(1, 1, 3, 5), QLineF(2, 0, 4, 5)));
  QVERIFY(linesCollinear(QLineF(1, 1, 3, 5), QLineF(5, 9, 7, 13)));
}

void TestGeometry::test_2D_segmentsIntersect_whenGivenFourFloatingPointPoints_shouldWork() {
  using namespace Geometry2D;

  QVERIFY(segmentsIntersect(QPointF(0, 0), QPointF(2, 4), QPointF(3, 1), QPointF(-1, 3)));
  QVERIFY(segmentsIntersect(QPointF(0, 0), QPointF(2, 4), QPointF(4, 3), QPointF(0, 5)));
  QVERIFY(segmentsIntersect(QPointF(0, 0), QPointF(2, 4), QPointF(2, -1), QPointF(-2, 1)));
  QVERIFY(!segmentsIntersect(QPointF(0, 0), QPointF(2, 4), QPointF(5, 5), QPointF(1, 7)));
}

void TestGeometry::test_2D_segmentsIntersect_whenGivenTwoLines_shouldWork() {
  using namespace Geometry2D;

  QVERIFY(segmentsIntersect(QLineF(0, 0, 2, 4), QLineF(3, 1, -1, 3)));
  QVERIFY(segmentsIntersect(QLineF(0, 0, 2, 4), QLineF(4, 3, 0, 5)));
  QVERIFY(segmentsIntersect(QLineF(0, 0, 2, 4), QLineF(2, -1, -2, 1)));
  QVERIFY(!segmentsIntersect(QLineF(0, 0, 2, 4), QLineF(5, 5, 1, 7)));
}

void TestGeometry::test_2D_pointInPolygon_whenGivenAPolygonAndAPoint_shouldWork() {
  using namespace Geometry2D;
  QPolygonF poly;
  poly += (QPointF(0, 0));
  poly << (QPointF(5, 0));
  poly.push_back(QPointF(5, 5));
  poly.append(QPointF(0, 5));

  QVERIFY(pointInPolygon(poly, QPointF(2, 2)));
  QVERIFY(pointInPolygon(poly, QPointF(2, 0)));
  QVERIFY(pointInPolygon(poly, QPointF(0, 2)));
  QVERIFY(!pointInPolygon(poly, QPointF(5, 2)));
  QVERIFY(!pointInPolygon(poly, QPointF(2, 5)));
}

void TestGeometry::test_2D_pointOnPolygon_whenGivenAPolygonAndAPoint_shouldWork() {
  using namespace Geometry2D;
  QPolygonF poly;
  poly += (QPointF(0, 0));
  poly << (QPointF(5, 0));
  poly.push_back(QPointF(5, 5));
  poly.append(QPointF(0, 5));

  QVERIFY(!pointOnPolygon(poly, QPointF(2, 2)));
  QVERIFY(pointOnPolygon(poly, QPointF(2, 0)));
  QVERIFY(pointOnPolygon(poly, QPointF(0, 2)));
  QVERIFY(pointOnPolygon(poly, QPointF(5, 2)));
  QVERIFY(pointOnPolygon(poly, QPointF(2, 5)));
}

QTEST_MAIN(TestGeometry)
