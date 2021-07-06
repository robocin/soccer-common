#ifndef SOCCER_COMMON_GEOMETRY_H
#define SOCCER_COMMON_GEOMETRY_H

#include <QPoint>
#include <QVector2D>
#include <QPolygon>
#include <QLine>
#include <cassert>
#include <type_traits>

#include "soccer-common/Math/Math.h"

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

namespace Geometry {
  static constexpr qreal PI = M_PI;

  /*!
   * @tparam T floating point type.
   * @param radians the value in radians.
   * @return This function converts the radians in T to degrees.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> radiansToDegrees(T radians) {
    return radians * (static_cast<T>(180) / static_cast<T>(PI));
  }

  /*!
   * @tparam T integral point type.
   * @param radians the value in radians.
   * @return This function converts the radians in T to degrees and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> radiansToDegrees(T radians) {
    return radiansToDegrees(static_cast<double>(radians));
  }

  /*!
   * @tparam T floating point type.
   * @param degrees the value in degrees.
   * @return This function converts the degrees in T to radians.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> degreesToRadians(T degrees) {
    return (degrees * static_cast<T>(PI)) / static_cast<T>(180);
  }

  /*!
   * @tparam T integral point type.
   * @param degrees the value in degrees.
   * @return This function converts the degrees in T to radians and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> degreesToRadians(T degrees) {
    return degreesToRadians(static_cast<double>(degrees));
  }

  /*!
   * @param lhs, rhs floating point values in radians.
   * @return Returns the signed smallest angle difference in radians.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> smallestAngleDiff(const T& lhs,
                                                                               const T& rhs) {
    T angle = Math::modularize<T>(rhs - lhs, static_cast<T>(2) * PI);
    if (angle >= PI) {
      return angle - static_cast<T>(2) * PI;
    } else if (angle < -PI) {
      return angle + static_cast<T>(2) * PI;
    }
    return angle;
  }

  /*!
   * @param value the value in degrees.
   * @return Returns the value in radians.
   */
  constexpr auto operator"" _degrees(long double value) {
    return Geometry::degreesToRadians(value);
  }

  /*!
   * @param value the value in degrees.
   * @return Returns the value in radians.
   */
  constexpr auto operator"" _degrees(unsigned long long value) {
    return Geometry::degreesToRadians(value);
  }

  /*!
   * @tparam T arithmetic type.
   * @param value The angle to normalize, in radians or degrees (depending on center and amplitude
   * values).
   * @param center The center of the angle interval. <br>
   *   if center == 0 and amplitude == π, the interval is [-π ; +π]. <br>
   *   if center == π and amplitude == π, the interval is [0 ; 2*π].
   * @param amplitude The amplitude of the angle, usually π in radians or 180 in degrees.
   * @return Normalizes the angle and returns the value between [-amplitude + center, +amplitude +
   * center].
   */
  template <class T>
  constexpr T normalizeAngle(T value, const T& center, const T& amplitude) {
    value = Math::modularize<T>(value, static_cast<T>(2) * amplitude);
    if (value < -amplitude + center) {
      value += static_cast<T>(2) * amplitude;
    } else if (value > amplitude + center) {
      value -= static_cast<T>(2) * amplitude;
    }
    return value;
  }

  /*!
   * @tparam T floating point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-π, +π].
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> normalizeInPI(const T& radians) {
    return normalizeAngle<T>(radians, 0, static_cast<T>(PI));
  }

  /*!
   * @tparam T floating point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-180, +180].
   */
  template <class T>
  constexpr std::enable_if_t<std::is_floating_point_v<T>, T> normalizeIn180(const T& degrees) {
    return normalizeAngle<T>(degrees, 0, static_cast<T>(180));
  }

  /*!
   * @tparam T integer point type.
   * @param radians The angle to normalize, in radians.
   * @return Normalizes the angle and returns the value between [-180, +180] in double.
   */
  template <class T>
  constexpr std::enable_if_t<std::is_integral_v<T>, double> normalizeIn180(const T& degrees) {
    return normalizeAngle<double>(degrees, 0, static_cast<double>(180));
  }
} // namespace Geometry

#ifndef GEOMETRY_UNDEF_PI
using Geometry::PI;
#endif

#ifndef GEOMETRY_UNDEF_LITERAL_OPERATOR_DEGREES
using Geometry::operator""_degrees;
#endif

namespace Geometry2D {
  using namespace Geometry;

  /*!
   * @brief Return the type of Point coordinates.
   */
  template <class PT>
  using CoordType =
      std::common_type_t<decltype(std::declval<PT>().x()), decltype(std::declval<PT>().y())>;

  /*!
   * @param lhs, rhs values to compare.
   * @return Compares lhs and rhs lexicographically by operator<, that is, compares the 'x' axis and
   * only if they are equivalent, compares the 'y' axis.
   */
  constexpr bool operator<(const QPoint& lhs, const QPoint& rhs) {
    return (lhs.x() != rhs.x()) ? (lhs.x() < rhs.x()) : (lhs.y() < rhs.y());
  }

  /*!
   * @param lhs, rhs values to compare.
   * @return Compares lhs and rhs lexicographically by operator<, that is, compares the 'x' axis and
   * only if they are equivalent, compares the 'y' axis.
   */
  constexpr bool operator<(const QPointF& lhs, const QPointF& rhs) {
    return (lhs.x() != rhs.x()) ? (lhs.x() < rhs.x()) : (lhs.y() < rhs.y());
  }

  /*!
   * @param lhs, rhs values to compare.
   * @return Compares lhs and rhs lexicographically by operator<, that is, compares the 'x' axis and
   * only if they are equivalent, compares the 'y' axis.
   */
  constexpr bool operator<(const QVector2D& lhs, const QVector2D& rhs) {
    return (lhs.x() != rhs.x()) ? (lhs.x() < rhs.x()) : (lhs.y() < rhs.y());
  }

  /*!
   * @return Returns a PT with the given angle and unitary length.
   */
  template <class PT>
  constexpr PT fromPolar(CoordType<PT> angle) {
    return PT(std::cos(angle), std::sin(angle));
  }

  /*!
   * @return Returns a PT with the given length and angle.
   */
  template <class PT>
  constexpr PT fromPolar(CoordType<PT> length, CoordType<PT> angle) {
    return PT(std::cos(angle) * length, std::sin(angle) * length);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members, and 'operator +' defined.
   * @param lhs, rhs values in PT to compute.
   * @return Returns the dot product (scalar product) of lhs and rhs.
   * @note dot product sign indicates whether two vectors point in about the same direction.
   */
  template <class PT>
  constexpr CoordType<PT> dot(const PT& lhs, const PT& rhs) {
    return (lhs.x() * rhs.x()) + (lhs.y() * rhs.y());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members, and 'operator -' defined.
   * @param lhs, rhs values in PT to compute.
   * @return Returns the cross product of lhs and rhs.
   * @note Using 'd' as the line through the vector lhs.
   * @note — if lhs ^ rhs > 0, then rhs points to the left side of d if we're looking in the
   * direction of a;
   * @note — if lhs ^ rhs = 0, then rhs lies on d, so it's collinear with a;
   * @note — if lhs ^ rhs < 0, then rhs points to the right side of d.
   * @note To sum it up, 2D cross product indicates whether the shortest turn from lhs to rhs is in
   * the counter-clockwise direction.
   */
  template <class PT>
  constexpr CoordType<PT> cross(const PT& lhs, const PT& rhs) {
    return (lhs.x() * rhs.y()) - (lhs.y() * rhs.x());
  }

  /*!
   * @tparam T Requires '+', '-' and '*' operators.
   * @param x1, y1, x2, y2 coordinates of points/vectors 1 and 2.
   * @return Returns the squared distance from the point/vector (x1, y1) to the point/vector (x2,
   * y2).
   */
  template <class T>
  constexpr T distanceSquared(T x1, T y1, T x2, T y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs values in PT to compute.
   * @return Returns the squared distance from lhs to rhs.
   */
  template <class PT>
  constexpr CoordType<PT> distanceSquared(const PT& lhs, const PT& rhs) {
    return distanceSquared<CoordType<PT>>(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  /*!
   * @tparam T Requires '+', '-' and '*' operators.
   * @param x1, y1, x2, y2 coordinates of points/vectors 1 and 2.
   * @return Returns the distance from the point/vector (x1, y1) to the point/vector (x2, y2).
   */
  template <class T>
  constexpr auto distance(T x1, T y1, T x2, T y2) {
    return std::sqrt(distanceSquared<T>(x1, y1, x2, y2));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs values in PT to compute.
   * @return Returns the distance from lhs to rhs.
   */
  template <class PT>
  constexpr auto distance(const PT& lhs, const PT& rhs) {
    return distance<CoordType<PT>>(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Returns a copy of p rotated in clockwise direction by 90 degrees.
   */
  template <class PT>
  constexpr PT rotateCW90(const PT& p) {
    return PT(p.y(), -p.x());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Returns a copy of p rotated in counter-clockwise direction by 90 degrees.
   */
  template <class PT>
  constexpr PT rotateCCW90(const PT& p) {
    return PT(-p.y(), p.x());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members (they must be floating point).
   * @tparam T type of the value to rotate.
   * @param p, t the vector and the value to rotate, in radians.
   * @return Returns a copy of p rotated in counter-clockwise direction by 90 degrees.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT>
  rotateCCW(const PT& p, CoordType<PT> t) {
    return PT(p.x() * std::cos(t) - p.y() * std::sin(t), p.x() * std::sin(t) + p.y() * std::cos(t));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Computes the arc tangent of p.y()/p.x() (i.e. the polar angle of the vector) using the
   * signs of arguments to determine the correct quadrant (in the range [-π , +π] radians).
   */
  template <class PT>
  constexpr auto angle(const PT& p) {
    return std::atan2(p.y(), p.x());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs the vectors.
   * @return Computes the angle between lhs and rhs (in the range [-π , +π] radians, the order
   * matters).
   */
  template <class PT>
  constexpr auto angleBetween(const PT& lhs, const PT& rhs) {
    return std::atan2(cross<PT>(lhs, rhs), dot<PT>(lhs, rhs));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Returns the squared length of the vector from the origin. This is equivalent to the dot
   * product of the vector with itself.
   */
  template <class PT>
  constexpr CoordType<PT> lengthSquared(const PT& p) {
    return dot<PT>(p, p);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Returns the length of the vector from the origin. This is equivalent to the square root
   * of dot product of the vector with itself.
   */
  template <class PT>
  constexpr auto length(const PT& p) {
    return std::sqrt(lengthSquared<PT>(p));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param p the vector.
   * @return Returns the sum of the absolute values of x() and y(), traditionally known as the
   * "Manhattan length" of the vector from the origin to the point.
   */
  template <class PT>
  constexpr CoordType<PT> manhattanLength(const PT& p) {
    return std::abs(p.x()) + std::abs(p.y());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members (they must be floating point).
   * @tparam T type of the value to resize.
   * @param p, t the vector and the value to resize.
   * @return Returns a copy of p resized with 't'.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT> resize(const PT& p,
                                                                                 CoordType<PT> t) {
    return static_cast<PT>(p / length(p) * t);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members (they must be floating point).
   * @tparam T type of the value to normalize.
   * @param p, t the vector and the value to normalize.
   * @return Returns a copy of p resized to 1.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT> normalize(const PT& p) {
    return resize<PT>(p, static_cast<CoordType<PT>>(1));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members (they must be integral).
   * @tparam T type of the value to normalize.
   * @param p, t the vector and the value to normalize.
   * @return Returns a copy of p integer normalized.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_integral_v<CoordType<PT>>, PT> normalize(const PT& p) {
    return p / std::gcd(std::abs(p.x()), std::abs(p.y()));
  }

  /*!
   * @param a, c, d positive sides of any triangle.
   * @return Returns if the sides can form a valid triangle.
   */
  template <class T>
  constexpr bool isTriangle(T a, T b, T c) {
    return (a + b) > c && (a + c) > b && (b + c) > a;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @return Returns the value of the signed area * 2.
   */
  template <class PT>
  CoordType<PT> signedArea2(const QVector<PT>& polygon) {
    if (polygon.size() < 3) {
      throw std::runtime_error("polygon size is less than 3.");
    }
    int n = static_cast<int>(polygon.size());
    CoordType<PT> ret = 0;
    for (int h = n - 1, i = 0; i < n; h = i++) {
      ret += cross<PT>(polygon[h], polygon[i]);
    }
    return ret;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @tparam T Equals to the common type returned by '.x()' and '.y()' by default.
   * @return Returns the value of the signed area.
   */
  template <class PT, class T = CoordType<PT>>
  auto signedArea(const QVector<PT>& polygon) {
    return signedArea2<PT>(polygon) / static_cast<T>(2);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @return Returns the value of the area * 2.
   */
  template <class PT>
  CoordType<PT> area2(const QVector<PT>& polygon) {
    return std::abs(signedArea2<PT>(polygon));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @tparam T Equals to the common type returned by '.x()' and '.y()' by default.
   * @return Returns the value of the area.
   */
  template <class PT, class T = CoordType<PT>>
  auto area(const QVector<PT>& polygon) {
    return area2<PT>(polygon) / static_cast<T>(2);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @return Returns the position of the centroid.
   * @note the centroid or geometric center of a plane figure is the arithmetic mean position of
   * all the points in the figure. Informally, it is the point at which a cutout of the shape could
   * be perfectly balanced on the tip of a pin.
   */
  template <class PT>
  std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT>
  centroid(const QVector<PT>& polygon) {
    PT ret(0, 0);
    const auto& scale = static_cast<CoordType<PT>>(6) * signedArea<PT>(polygon);
    int n = static_cast<int>(polygon.size());
    for (int h = n - 1, i = 0; i < n; h = i++) {
      ret += (polygon[h] + polygon[i]) * cross<PT>(polygon[h], polygon[i]);
    }

    return ret / scale;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c line through (a, b) and point c.
   * @return Projects the point c onto line through a and b.
   * @note assuming a != b.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT>
  projectPointLine(const PT& a, const PT& b, const PT& c) {
    if (a == b) {
      throw std::runtime_error("'a' and 'b' doesn't define a line.");
    }
    return a + (b - a) * dot<PT>(b - a, c - a) / static_cast<CoordType<PT>>(dot(b - a, b - a));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param line, c line and point c.
   * @return Projects the point c onto line.
   * @note assuming line.p1() != line.p2().
   */
  template <class PT>
  constexpr PT projectPointLine(const QLineF& line, const PT& c) {
    return projectPointLine<PT>(line.p1(), line.p2(), c);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c line through (a, b) and point c.
   * @return Returns the distance between the point c and his projection onto line defined by a and
   * b.
   * @note assuming a != b.
   */
  template <class PT>
  constexpr auto distancePointLine(const PT& a, const PT& b, const PT& c) {
    return distance<PT>(c, projectPointLine<PT>(a, b, c));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param line, c line and point c.
   * @return Returns the distance between the point c and his projection onto line.
   * @note assuming line.p1() != line.p2().
   */
  template <class PT>
  constexpr auto distancePointLine(const QLineF& line, const PT& c) {
    return distance<PT>(c, projectPointLine<PT>(line.p1(), line.p2(), c));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c line through (a, b) and point c.
   * @return Reflects the point c onto line through a and b.
   * @note assuming a != b.
   */
  template <class PT>
  constexpr PT reflectPointLine(const PT& a, const PT& b, const PT& c) {
    return static_cast<CoordType<PT>>(2) * projectPointLine<PT>(a, b, c) - c;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param line, c line and point c.
   * @return Reflects the point c onto line.
   * @note assuming line.p1() != line.p2().
   */
  template <class PT>
  constexpr PT reflectPointLine(const QLineF& line, const PT& c) {
    return reflectPointLine<PT>(line.p1(), line.p2(), c);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c line through (a, b) and point c.
   * @return Projects the point c onto segment through a and b.
   * @note assuming a != b.
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, PT>
  projectPointSegment(const PT& a, const PT& b, const PT& c) {
    if (a == b) {
      throw std::runtime_error("'a' and 'b' doesn't define a line.");
    }
    CoordType<PT> r = dot<PT>(b - a, b - a);
    if (Math::isNull(r)) {
      return a;
    }
    r = dot<PT>(c - a, b - a) / r;
    if (r < 0) {
      return a;
    } else if (r > 1) {
      return b;
    } else {
      return a + (b - a) * r;
    }
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param line, c line and point c.
   * @return Projects the point c onto segment line.
   * @note assuming line.p1() != line.p2().
   */
  template <class PT>
  constexpr PT projectPointSegment(const QLineF& line, const PT& c) {
    return projectPointSegment<PT>(line.p1(), line.p2(), c);
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c line through (a, b) and point c.
   * @return Returns the distance between the point c and his projection onto segment defined by a
   * and b.
   * @note assuming a != b.
   */
  template <class PT>
  constexpr auto distancePointSegment(const PT& a, const PT& b, const PT& c) {
    return distance<PT>(c, projectPointSegment<PT>(a, b, c));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param line, c line and point c.
   * @return Returns the distance between the point c and his projection onto segment.
   * @note assuming line.p1() != line.p2().
   */
  template <class PT>
  constexpr auto distancePointSegment(const QLineF& line, const PT& c) {
    return distance<PT>(c, projectPointSegment<PT>(line.p1(), line.p2(), c));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c, d lines (a, b) and (c, d).
   * @return Determines if lines through (a, b) and (c, d) are parallel.
   */
  template <class PT>
  constexpr bool linesParallel(const PT& a, const PT& b, const PT& c, const PT& d) {
    return Math::isNull(cross<PT>(b - a, c - d));
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs lines.
   * @return Determines if lines through lhs and rhs are parallel.
   */
  constexpr bool linesParallel(const QLineF& lhs, const QLineF& rhs) {
    return linesParallel<QPointF>(lhs.p1(), lhs.p2(), rhs.p1(), rhs.p2());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c, d lines (a, b) and (c, d).
   * @return Determines if lines through (a, b) and (c, d) are collinear.
   */
  template <class PT>
  constexpr bool linesCollinear(const PT& a, const PT& b, const PT& c, const PT& d) {
    if (!linesParallel<PT>(a, b, c, d)) {
      return false;
    }
    if (!Math::isNull(cross<PT>(a - b, a - c))) {
      return false;
    }
    if (!Math::isNull(cross<PT>(c - d, c - a))) {
      return false;
    }
    return true;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs lines.
   * @return Determines if lines through lhs and rhs are collinear.
   */
  constexpr bool linesCollinear(const QLineF& lhs, const QLineF& rhs) {
    return linesCollinear<QPointF>(lhs.p1(), lhs.p2(), rhs.p1(), rhs.p2());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c, d lines (a, b) and (c, d).
   * @return Determines if line segment from a to b intersects with line segment from c to d.
   */
  template <class PT>
  constexpr bool segmentsIntersect(const PT& a, const PT& b, const PT& c, const PT& d) {
    if (linesCollinear<PT>(a, b, c, d)) {
      if (Math::isNull(distanceSquared<PT>(a, c)) || Math::isNull(distanceSquared<PT>(a, d)) ||
          Math::isNull(distanceSquared<PT>(b, c)) || Math::isNull(distanceSquared<PT>(b, d))) {
        return true;
      }
      if (dot<PT>(c - a, c - b) > 0 && dot<PT>(d - a, d - b) > 0 && dot<PT>(c - b, d - b) > 0) {
        return false;
      }
      return true;
    }
    if (cross<PT>(d - a, b - a) * cross<PT>(c - a, b - a) > 0) {
      return false;
    }
    if (cross<PT>(a - c, d - c) * cross<PT>(b - c, d - c) > 0) {
      return false;
    }
    return true;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs lines.
   * @return Determines if line segment lhs intersects with line segment rhs.
   */
  constexpr bool segmentsIntersect(const QLineF& lhs, const QLineF& rhs) {
    return segmentsIntersect<QPointF>(lhs.p1(), lhs.p2(), rhs.p1(), rhs.p2());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c, d lines (a, b) and (c, d).
   * @return Returns the intersection point between the two lines (if exists).
   * @note implementation is based on Graphics Gems III's "Faster Line Segment Intersection"
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, std::optional<PT>>
  linesIntersection(const PT& a, const PT& b, const PT& c, const PT& d) {
    const PT ba = b - a;
    const PT cd = c - d;
    const PT ac = a - c;
    const CoordType<PT> denominator = cross<PT>(cd, ba);
    if (Math::isNull(denominator)) {
      return std::nullopt;
    }
    const CoordType<PT> reciprocal = static_cast<CoordType<PT>>(1) / denominator;
    const CoordType<PT> na = cross<PT>(ac, cd) * reciprocal;
    return a + ba * na;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs lines.
   * @return Returns the intersection point between the two lines (if exists).
   * @note implementation is based on Graphics Gems III's "Faster Line Segment Intersection"
   */
  constexpr auto linesIntersection(const QLineF& lhs, const QLineF& rhs) {
    return linesIntersection<QPointF>(lhs.p1(), lhs.p2(), rhs.p1(), rhs.p2());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param a, b, c, d lines (a, b) and (c, d).
   * @return Returns the intersection point between the two segments (if exists).
   * @note implementation is based on Graphics Gems III's "Faster Line Segment Intersection"
   */
  template <class PT>
  constexpr std::enable_if_t<std::is_floating_point_v<CoordType<PT>>, std::optional<PT>>
  segmentsIntersection(const PT& a, const PT& b, const PT& c, const PT& d) {
    const PT ba = b - a;
    const PT cd = c - d;
    const PT ac = a - c;
    const CoordType<PT> denominator = cross<PT>(cd, ba);
    if (Math::isNull(denominator)) {
      return std::nullopt;
    }
    const CoordType<PT> reciprocal = static_cast<CoordType<PT>>(1) / denominator;
    const CoordType<PT> na = cross<PT>(ac, cd) * reciprocal;
    if (!(0 <= na && na <= 1)) {
      return std::nullopt;
    }
    const CoordType<PT> nb = cross<PT>(ba, ac) * reciprocal;
    if (!(0 <= nb && nb <= 1)) {
      return std::nullopt;
    }
    return a + ba * na;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param lhs, rhs lines.
   * @return Returns the intersection point between the two segments (if exists).
   * @note implementation is based on Graphics Gems III's "Faster Line Segment Intersection"
   */
  constexpr auto segmentsIntersection(const QLineF& lhs, const QLineF& rhs) {
    return segmentsIntersection<QPointF>(lhs.p1(), lhs.p2(), rhs.p1(), rhs.p2());
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @param polygon the given polygon.
   * @param unsorted determines if it's necessary to sort with respect to x-coordinates (with
   * respect to y-coordinates in case of a tie in x-coordinates).
   * @return Returns the convex hull of the given points using the Andrew's Monotone Chain
   * Algorithm.
   */
  template <class PT>
  QVector<PT> convexHull(QVector<PT> polygon, bool unsorted = true) {
    if (unsorted) {
      std::sort(polygon.begin(), polygon.end(), [](const PT& lhs, const PT& rhs) {
        return std::pair(lhs.x(), lhs.y()) < std::pair(rhs.x(), rhs.y());
      });
    }
    polygon.resize(std::unique(polygon.begin(), polygon.end()) - polygon.begin());
    if (polygon.size() <= 1) {
      return polygon;
    }
    QVector<PT> ans(polygon.size() + polygon.size() + 1);
    int s = 0;
    int n = static_cast<int>(polygon.size());
    for (int i = 0; i < n; ++i) {
      while (s > 1 && cross<PT>(polygon[i] - ans[s - 2], ans[s - 1] - ans[s - 2]) >= 0) {
        --s;
      }
      ans[s++] = polygon[i];
    }
    for (int i = n - 2, t = s + 1; i >= 0; --i) {
      while (s >= t && cross<PT>(polygon[i] - ans[s - 2], ans[s - 1] - ans[s - 2]) >= 0) {
        --s;
      }
      ans[s++] = polygon[i];
    }
    ans.resize(s - 1);
    return ans;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @return Determines if point is in a possibly non-convex polygon (by William Randolph Franklin);
   * returns 1 for strictly interior points, 0 for strictly exterior points, and 0 or 1 for the
   * remaining points.
   * @note It's possible to convert this into an *exact* test using integer arithmetic by taking
   * care of the division appropriately (making sure to deal with signs properly) and then by
   * writing exact tests for checking point on polygon boundary.
   * @note Be careful: Because of this, this function allows integer point types.
   */
  template <class PT>
  bool pointInPolygon(const QVector<PT>& polygon, const PT& p) {
    int n = static_cast<int>(polygon.size());
    bool c = false;
    for (int i = 0; i < n; ++i) {
      int j = (i + 1) % n;
      if (polygon[i].y() <= p.y() && p.y() < polygon[j].y() ||
          polygon[j].y() <= p.y() && p.y() < polygon[i].y()) {
        if (p.x() < (polygon[i].x() + (polygon[j].x() - polygon[i].x()) * (p.y() - polygon[i].y()) /
                                          (polygon[j].y() - polygon[i].y()))) {
          c = !c;
        }
      }
    }
    return c;
  }

  /*!
   * @tparam PT Requires '.x()' and '.y()' members.
   * @return Determines if point is on the boundary of a polygon.
   */
  template <class PT>
  bool pointOnPolygon(const QVector<PT>& polygon, const PT& p) {
    int n = static_cast<int>(polygon.size());
    for (int i = 0; i < n; ++i) {
      if (PT proj = projectPointSegment<PT>(polygon[i], polygon[(i + 1) % n], p);
          Math::isNull(distanceSquared<PT>(proj, p))) {
        return true;
      }
    }
    return false;
  }

} // namespace Geometry2D

#endif // SOCCER_COMMON_GEOMETRY_H
