#ifndef SOCCER_COMMON_GEOMETRY_H
#define SOCCER_COMMON_GEOMETRY_H

#include <QPoint>
#include <QVector2D>
#include <QPolygon>
#include <QLine>
#include <QtGlobal>
#include <cmath>
#include <cassert>
#include <type_traits>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

template <class T>
class Extends;

namespace Geometry {
  static constexpr qreal PI = M_PI;

  namespace Detail {
    /*!
     * @tparam T arithmetic type.
     * @return Returns true if T is float and the absolute value of f is within 0.00001f of 0.0.
     * @return Returns true if T is double and the absolute value of d is within 0.000000000001 of
     * 0.0.
     * @return Returns true if T is an integer type and equals to 0.
     */
    template <class T>
    inline constexpr bool isNull(const T& value) noexcept {
      if constexpr (std::is_floating_point_v<T>) {
        return qFuzzyIsNull(value);
      } else {
        return value == 0;
      }
    }
  } // namespace Detail

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
   * @tparam T non floating point type.
   * @param radians the value in radians.
   * @return This function converts the radians in T to degrees and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<!std::is_floating_point_v<T>, T> radiansToDegrees(T radians) {
    return radiansToDegrees<double>(radians);
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
   * @tparam T non floating point type.
   * @param degrees the value in degrees.
   * @return This function converts the degrees in T to radians and returns in double.
   */
  template <class T>
  constexpr std::enable_if_t<!std::is_floating_point_v<T>, T> degreesToRadians(T degrees) {
    return degreesToRadians<double>(degrees);
  }
} // namespace Geometry

#ifndef GEOMETRY_UNDEF_PI
using Geometry::PI;
#endif

namespace Geometry2D {
  using namespace Geometry;

  template <class PT>
  using CoordType =
      std::common_type_t<decltype(std::declval<PT>().x()), decltype(std::declval<PT>().y())>;

  // Extends<QPointF> will be used as standard 2D point.
  using Point [[maybe_unused]] = Extends<QPointF>;

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
  constexpr auto lengthSquared(const PT& p) {
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
  constexpr PT normalize(const PT& p) {
    return resize<PT>(p, static_cast<CoordType<PT>>(1));
  }

  /*!
   * @param a, c, d positive sides of any triangle.
   * @return Return if the sides can form a valid triangle.
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

    CoordType<PT> ret = 0;
    for (int h = polygon.size() - 1, i = 0; i < polygon.size(); h = i++) {
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
    const auto& scale = 6.0 * signedArea<PT>(polygon);

    for (int h = polygon.size() - 1, i = 0; i < polygon.size(); h = i++) {
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
   * @return return the distance between the point c and his projection onto line defined by a and
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
   * @return return the distance between the point c and his projection onto line.
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
    if (Detail::isNull(r)) {
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
   * @return return the distance between the point c and his projection onto segment defined by a
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
   * @return return the distance between the point c and his projection onto segment.
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
    return Detail::isNull(cross<PT>(b - a, c - d));
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
    if (!Detail::isNull(cross<PT>(a - b, a - c))) {
      return false;
    }
    if (!Detail::isNull(cross<PT>(c - d, c - a))) {
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
      if (Detail::isNull(distanceSquared<PT>(a, c)) || Detail::isNull(distanceSquared<PT>(a, d)) ||
          Detail::isNull(distanceSquared<PT>(b, c)) || Detail::isNull(distanceSquared<PT>(b, d))) {
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
   * @return Determines if point is in a possibly non-convex polygon (by William Randolph Franklin);
   * returns 1 for strictly interior points, 0 for strictly exterior points, and 0 or 1 for the
   * remaining points.
   * @note It's possible to convert this into an *exact* test using integer arithmetic by taking
   * care of the division appropriately (making sure to deal with signs properly) and then by
   * writing exact tests for checking point on polygon boundary.
   * @note Be careful: Because of this, this function allows integer types.
   */
  template <class PT>
  bool pointInPolygon(const QVector<PT>& polygon, const PT& p) {
    bool c = false;
    for (int i = 0; i < polygon.size(); ++i) {
      int j = (i + 1) % polygon.size();
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
    for (int i = 0; i < polygon.size(); ++i) {
      if (PT proj = projectPointSegment<PT>(polygon[i], polygon[(i + 1) % polygon.size()], p);
          Detail::isNull(distanceSquared<PT>(proj, p))) {
        return true;
      }
    }
    return false;
  }

} // namespace Geometry2D

#ifndef GEOMETRY_2D_UNDEF_POINT
using Geometry2D::Point;
#endif

#endif // SOCCER_COMMON_GEOMETRY_H
