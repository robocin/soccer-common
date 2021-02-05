#ifndef SOCCER_COMMON_GEOMETRY_H
#define SOCCER_COMMON_GEOMETRY_H

#include <QPoint>
#include <QPolygon>
#include <QLine>
#include <cmath>
#include <cassert>
#include <type_traits>

#define RC_T_TEMPLATE template <class T>

#define RC_PT_T_TEMPLATE                                                       \
  template <class PT, class T = decltype(std::declval<PT>().x())>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

namespace Geometry {
  static constexpr qreal PI = M_PI;

  RC_T_TEMPLATE qreal radiansToDegrees(T radians) {
    return radians * (180.0 / PI);
  }

  RC_T_TEMPLATE qreal degreesToRadians(T degrees) {
    return (degrees * PI) / 180.0;
  }
} // namespace Geometry

using Geometry::PI;

namespace Geometry2D {
  using namespace Geometry;

  RC_PT_T_TEMPLATE bool operator<(const PT& lhs, const PT& rhs) {
    return (lhs.x() != rhs.x()) ? (lhs.x() < rhs.x()) : (lhs.y() < rhs.y());
  }

  RC_PT_T_TEMPLATE T dot(const PT& lhs, const PT& rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y();
  }

  RC_PT_T_TEMPLATE T cross(const PT& lhs, const PT& rhs) {
    return lhs.x() * rhs.y() - lhs.y() * rhs.x();
  }

  RC_T_TEMPLATE T distanceSquared(T x1, T y1, T x2, T y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  }

  RC_PT_T_TEMPLATE T distanceSquared(const PT& lhs, const PT& rhs) {
    return distanceSquared(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  RC_T_TEMPLATE qreal distance(T x1, T y1, T x2, T y2) {
    return std::sqrt(distanceSquared(x1, y1, x2, y2));
  }

  RC_PT_T_TEMPLATE qreal distance(const PT& lhs, const PT& rhs) {
    return distance(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  RC_PT_T_TEMPLATE PT rotateCW90(const PT& p) {
    return PT(p.y(), -p.x());
  }

  RC_PT_T_TEMPLATE PT rotateCCW90(const PT& p) {
    return PT(-p.y(), p.x());
  }

  RC_PT_T_TEMPLATE PT rotateCCW(const PT& p, qreal t) {
    static_assert(std::is_floating_point_v<T>);
    return PT(p.x() * std::cos(t) - p.y() * std::sin(t),
              p.x() * std::sin(t) + p.y() * std::cos(t));
  }

  RC_PT_T_TEMPLATE qreal angle(const PT& p) {
    return std::atan2(p.y(), p.x());
  }

  RC_PT_T_TEMPLATE qreal angleBetween(const PT& lhs, const PT& rhs) {
    return std::atan2(cross(lhs, rhs), dot(lhs, rhs));
  }

  RC_PT_T_TEMPLATE qreal length(const PT& p) {
    return std::sqrt(dot(p, p));
  }

  RC_PT_T_TEMPLATE T manhattanLength(const PT& p) {
    return std::abs(p.x()) + std::abs(p.y());
  }

  RC_PT_T_TEMPLATE PT resize(const PT& p, qreal t) {
    static_assert(std::is_floating_point_v<T>);
    return static_cast<PT>(p / length(p) * t);
  }

  RC_PT_T_TEMPLATE PT normalize(const PT& p) {
    return resize(p, 1.0);
  }

  RC_T_TEMPLATE bool isTriangle(T a, T b, T c) {
    return (a + b) > c && (a + c) > b && (b + c) > a;
  }

  RC_PT_T_TEMPLATE T signedArea2(const QVector<PT>& polygon) {
    if (polygon.size() < 3) {
      throw std::runtime_error("polygon size is less than 3.");
    }

    T ret = 0;
    for (int h = polygon.size() - 1, i = 0; i < polygon.size(); h = i++) {
      ret += cross(polygon[h], polygon[i]);
    }
    return ret;
  }

  RC_PT_T_TEMPLATE qreal signedArea(const QVector<PT>& polygon) {
    return static_cast<qreal>(signedArea2(polygon)) / 2.0;
  }

  RC_PT_T_TEMPLATE T area2(const QVector<PT>& polygon) {
    return std::abs(signedArea2(polygon));
  }

  RC_PT_T_TEMPLATE qreal area(const QVector<PT>& polygon) {
    return static_cast<qreal>(area2(polygon)) / 2.0;
  }

  RC_PT_T_TEMPLATE PT centroid(const QVector<PT>& polygon) {
    static_assert(std::is_floating_point_v<T>);

    PT ret(0, 0);
    const qreal& scale = 6.0 * signedArea(polygon);

    for (int h = polygon.size() - 1, i = 0; i < polygon.size(); h = i++) {
      ret += (polygon[h] + polygon[i]) * cross(polygon[h], polygon[i]);
    }

    return ret / scale;
  }

  RC_PT_T_TEMPLATE PT projectPointLine(const PT& a, const PT& b, const PT& c) {
    static_assert(std::is_floating_point_v<T>);
    if (a == b) {
      throw std::runtime_error("'a' and 'b' doesn't define a line.");
    }
    return a +
           (b - a) * dot(b - a, c - a) / static_cast<qreal>(dot(b - a, b - a));
  }

  RC_PT_T_TEMPLATE PT projectPointLine(const QLineF& line, const PT& c) {
    return projectPointLine<PT, T>(line.p1(), line.p2(), c);
  }

  RC_PT_T_TEMPLATE PT reflectPointLine(const PT& a, const PT& b, const PT& c) {
    return 2.0 * projectPointLine(a, b, c) - c;
  }

  RC_PT_T_TEMPLATE PT reflectPointLine(const QLineF& line, const PT& c) {
    return reflectPointLine<PT, T>(line.p1(), line.p2(), c);
  }
} // namespace Geometry2D

namespace Geometry3D {
  // Implementations can use the QVector3D class.
} // namespace Geometry3D

#undef RC_T_TEMPLATE
#undef RC_PT_T_TEMPLATE

#endif // SOCCER_COMMON_GEOMETRY_H
