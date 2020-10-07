#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPoint>
#include <QPolygon>
#include <cmath>
#include <cassert>
#include <type_traits>

#define RC_CONSTEXPR constexpr
#define RC_T_TEMPLATE_CONSTEXPR                                                \
  template <class T>                                                           \
  RC_CONSTEXPR
#define RC_PT_T_TEMPLATE_CONSTEXPR                                             \
  template <class PT, class T = decltype(std::declval<PT>().x())>              \
  RC_CONSTEXPR

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

namespace Geometry {
  static constexpr qreal PI = M_PI;

  RC_T_TEMPLATE_CONSTEXPR qreal radiansToDegrees(T radians) {
    return radians * (180.0 / PI);
  }

  RC_T_TEMPLATE_CONSTEXPR qreal degreesToRadians(T degrees) {
    return (degrees * PI) / 180.0;
  }
} // namespace Geometry

namespace Geometry2D {
  using namespace Geometry;

  RC_PT_T_TEMPLATE_CONSTEXPR T dot(const PT& lhs, const PT& rhs) {
    return PT::dotProduct(lhs, rhs);
  }

  RC_PT_T_TEMPLATE_CONSTEXPR T cross(const PT& lhs, const PT& rhs) {
    return lhs.x() * rhs.y() - lhs.y() * rhs.x();
  }

  RC_T_TEMPLATE_CONSTEXPR T distanceSquare(T x1, T y1, T x2, T y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  }

  RC_PT_T_TEMPLATE_CONSTEXPR T distanceSquare(const PT& lhs, const PT& rhs) {
    return distanceSquare(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  RC_T_TEMPLATE_CONSTEXPR qreal distance(T x1, T y1, T x2, T y2) {
    return std::sqrt(distanceSquare(x1, y1, x2, y2));
  }

  RC_PT_T_TEMPLATE_CONSTEXPR qreal distance(const PT& lhs, const PT& rhs) {
    return distance(lhs.x(), lhs.y(), rhs.x(), rhs.y());
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT rotateCW90(const PT& p) {
    return PT(p.y(), -p.x());
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT rotateCCW90(const PT& p) {
    return PT(-p.y(), p.x());
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT rotateCCW(const PT& p, qreal t) {
    static_assert(std::is_floating_point_v<T>);
    return PT(p.x() * std::cos(t) - p.y() * std::sin(t),
              p.x() * std::sin(t) + p.y() * std::cos(t));
  }

  RC_PT_T_TEMPLATE_CONSTEXPR qreal angle(const PT& lhs, const PT& rhs) {
    return std::atan2(cross(lhs, rhs), dot(lhs, rhs));
  }

  RC_PT_T_TEMPLATE_CONSTEXPR qreal length(const PT& p) {
    return std::sqrt(dot(p, p));
  }

  RC_CONSTEXPR int manhattanLength(const QPoint& p) {
    return p.manhattanLength();
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT resize(const PT& p, qreal t) {
    static_assert(std::is_floating_point_v<T>);
    return p / length(p) * t;
  }

  RC_T_TEMPLATE_CONSTEXPR bool isTriangle(T a, T b, T c) {
    return (a + b) > c && (a + c) > b && (b + c) > a;
  }

  RC_PT_T_TEMPLATE_CONSTEXPR T area2(const PT& a, const PT& b, const PT& c) {
    return (b.x() - a.x()) * (c.y() - a.y()) -
           (c.x() - a.x()) * (b.y() - a.y());
  }

  RC_PT_T_TEMPLATE_CONSTEXPR qreal area(const PT& a, const PT& b, const PT& c) {
    return static_cast<qreal>(area2(a, b, c)) / 2.0;
  }

  RC_PT_T_TEMPLATE_CONSTEXPR T area2(const QVector<PT>& polygon) {
    if (polygon.size() < 3) {
      throw std::runtime_error("polygon size is less than 3.");
    }

    T ret = 0;

    for (int i = 1; i + 1 < polygon.size(); ++i) {
      ret += area2(polygon[0], polygon[i], polygon[i + 1]);
    }

    return ret;
  }

  RC_PT_T_TEMPLATE_CONSTEXPR qreal area(const QVector<PT>& polygon) {
    return static_cast<qreal>(area2(polygon)) / 2.0;
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT projectPointLine(const PT& a,
                                                 const PT& b,
                                                 const PT& c) {
    static_assert(std::is_floating_point_v<T>);
    if (a == b) {
      throw std::runtime_error("'a' and 'b' doesn't define a line.");
    }
    return a +
           (b - a) * dot(b - a, c - a) / static_cast<qreal>(dot(b - a, b - a));
  }

  RC_PT_T_TEMPLATE_CONSTEXPR PT reflectPointLine(const PT& a,
                                                 const PT& b,
                                                 const PT& c) {
    return 2.0 * projectPointLine(a, b, c) - c;
  }
} // namespace Geometry2D

#undef RC_CONSTEXPR
#undef RC_T_TEMPLATE_CONSTEXPR
#undef RC_PT_T_TEMPLATE_CONSTEXPR

#endif // GEOMETRY_H
