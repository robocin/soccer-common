#include <QtTest>

#include "soccer-common/Geometry/Geometry.h"

class TestGeometry : public QObject {
  Q_OBJECT

 public:
  TestGeometry();
  ~TestGeometry();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void test_radiansToDegrees_whenGivenAFloatingPoint_shouldWork();
  void test_degreesToRadians_whenGivenAFloatingPoint_shouldWork();
  void test_operator_degrees_whenGivenAFloatingPoint_shouldWork();
  void test_smallestAngleDiff_whenGivenTwoFloatingPointNumbers_shouldWork();
  void test_normalizeAngle_whenGivenThreeFloatingPointNumbers_shouldWork();
  void test_normalizeInPI_whenGivenAFloatingPoint_shouldWork();
  void test_normalizeIn180_whenGivenAFloatingPoint_shouldWork();
  void test_2D_operatorLess_whenGivenTwoPoints_shouldWork();
  void test_2D_fromPolar_whenGivenAFloatingPoint_shouldWork();
  void test_2D_fromPolar_whenGivenTwoFloatingPointNumbers_shouldWork();
  void test_2D_dot_whenGivenTwoPoints_shouldWork();
  void test_2D_cross_whenGivenTwoPoints_shouldWork();
  void test_2D_distanceSquared_whenGivenFourNumbers_shouldWork();
  void test_2D_distanceSquared_whenGivenTwoPoints_shouldWork();
  void test_2D_distance_whenGivenFourNumbers_shouldWork();
  void test_2D_distance_whenGivenTwoPoints_shouldWork();
  void test_2D_rotateCW90_whenGivenAPoint_shouldWork();
  void test_2D_rotateCCW90_whenGivenAPoint_shouldWork();
  void test_2D_rotateCW_whenGivenAFloatingPointPoint_shouldWork();
  void test_2D_rotateCCW_whenGivenAFloatingPointPoint_shouldWork();
  void test_2D_angle_whenGivenAPoint_shouldWork();
  void test_2D_angleBetween_whenGivenTwoPoints_shouldWork();
  void test_2D_lengthSquared_whenGivenAPoint_shouldWork();
  void test_2D_length_whenGivenAPoint_shouldWork();
  void test_2D_norm_whenGivenAPoint_shouldWork();
  void test_2D_manhattanLength_whenGivenAPoint_shouldWork();
  void test_2D_unitaryAxisDirection_whenGivenAPoint_shouldWork();
  void test_2D_resize_whenGivenAFloatingPointPointAndAFloatingPoint_shouldWork();
  void test_2D_normalize_whenGivenAFloatingPointPoint_shouldWork();
  void test_2D_normalize_whenGivenAnIntegerPoint_shouldWork();
  void test_2D_isTriangle_whenGivenThreeNumbers_shouldWork();
  void test_2D_signedArea2_whenGivenAPolygon_shouldWork();
  void test_2D_signedArea_whenGivenAPolygon_shouldWork();
  void test_2D_area2_whenGivenAPolygon_shouldWork();
  void test_2D_area_whenGivenAPolygon_shouldWork();
  void test_2D_centroid_whenGivenAPolygonOfFloatingPointPoints_shouldWork();
  void test_2D_projectPointLine_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_distancePointLine_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_reflectPointLine_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_isOnTheLeft_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_isOnTheRight_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_projectPointSegment_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_distancePointSegment_whenGivenThreeFloatingPointPoints_shouldWork();
  void test_2D_linesParallel_whenGivenFourPoints_shouldWork();
  void test_2D_linesCollinear_whenGivenFourPoints_shouldWork();
  void test_2D_segmentsIntersect_whenGivenFourFloatingPointPoints_shouldWork();
  void test_2D_linesIntersection_whenGivenFourFloatingPointPoints_shouldWork();
  void test_2D_segmentsIntersection_whenGivenFourFloatingPointPoints_shouldWork();
  void test_2D_convexHull_whenGivenAPolygon_shouldWork();
  void test_2D_pointInPolygon_whenGivenAPolygonAndAPoint_shouldWork();
  void test_2D_pointOnPolygon_whenGivenAPolygonAndAPoint_shouldWork();
};
