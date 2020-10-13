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

void TestGeometry::testDistance() {
  QPoint first(0, 0);
  QPoint second(3, 4);

  QVERIFY(Geometry2D::distance(first, second) == 5);
}

QTEST_MAIN(TestGeometry)
