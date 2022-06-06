#ifndef SOCCER_COMMON_POINT2D_H
#define SOCCER_COMMON_POINT2D_H

#include <concepts>

#include <QDebug>
#include <QPoint>
#include <QPointF>
#include <QVector2D>
#include <QVector3D>

#include "soccer-common/Math/Math.h"

template <class T>
struct Point2D {
  using type = T;
  using coord_type = T;

  T x, y;

  // constructors:
  inline constexpr Point2D() : x(0), y(0) {
  }
  inline constexpr Point2D(T x, T y) : x(x), y(y) {
  }
  template <class U>
  inline constexpr explicit Point2D(const Point2D<U>& point) :
      x(static_cast<T>(point.x)),
      y(static_cast<T>(point.y)) {
  }
  template <class U, class V>
  inline constexpr explicit Point2D(const std::pair<U, V>& pair) :
      x(static_cast<T>(pair.first)),
      y(static_cast<T>(pair.second)) {
  }
  inline constexpr explicit Point2D(const QPoint& point) :
      x(static_cast<T>(point.x())),
      y(static_cast<T>(point.y())) {
  }
  inline constexpr explicit Point2D(const QPointF& point) :
      x(static_cast<T>(point.x())),
      y(static_cast<T>(point.y())) {
  }
  inline constexpr explicit Point2D(const QVector2D& vector) :
      x(static_cast<T>(vector.x())),
      y(static_cast<T>(vector.y())) {
  }
  inline constexpr explicit Point2D(const QVector3D& vector) :
      x(static_cast<T>(vector.x())),
      y(static_cast<T>(vector.y())) {
  }

  // static methods:
  inline static constexpr Point2D null() {
    return Point2D(0, 0);
  }
  inline static constexpr Point2D fromPolar(T angle) requires(std::floating_point<T>) {
    return Point2D(std::cos(angle), std::sin(angle));
  }
  inline static constexpr Point2D fromPolar(T length, T angle) requires(std::floating_point<T>) {
    return Point2D(std::cos(angle) * length, std::sin(angle) * length);
  }

  // integral comparison:
  inline constexpr bool operator==(const Point2D& other) const requires(std::integral<T>) = default;
  inline constexpr auto operator<=>(const Point2D& other) const
      requires(std::integral<T>) = default;

  // floating-point comparison:
  inline constexpr bool operator==(const Point2D& other) const requires(std::floating_point<T>) {
    return Math::isNull(other.x - x) and Math::isNull(other.y - y);
  }
  inline constexpr auto operator<=>(const Point2D& other) const requires(std::floating_point<T>) {
    if (Math::isNull(other.x - x)) {
      if (Math::isNull(other.y - y)) {
        return std::strong_ordering::equivalent;
      }
      if (y < other.y) {
        return std::strong_ordering::less;
      }
      if (y > other.y) {
        return std::strong_ordering::greater;
      }
    }
    if (x < other.x) {
      return std::strong_ordering::less;
    }
    return std::strong_ordering::greater;
  }

  // arithmetic-assignment operators:
  inline constexpr Point2D& operator+=(const Point2D& other) {
    x += other.x, y += other.y;
    return *this;
  }
  inline constexpr Point2D& operator-=(const Point2D& other) {
    x -= other.x, y -= other.y;
    return *this;
  }
  inline constexpr Point2D& operator*=(T factor) {
    x *= factor, y *= factor;
    return *this;
  }
  inline constexpr Point2D& operator/=(T factor) {
    x /= factor, y /= factor;
    return *this;
  }

  // arithmetic operators:
  inline constexpr Point2D operator+(const Point2D& other) const {
    return Point2D(*this) += other;
  }
  inline constexpr Point2D operator-(const Point2D& other) const {
    return Point2D(*this) -= other;
  }
  inline constexpr Point2D operator*(T factor) const {
    return Point2D(*this) *= factor;
  }
  inline constexpr Point2D operator/(T factor) const {
    return Point2D(*this) /= factor;
  }

  // arithmetic friends:
  friend inline constexpr Point2D operator*(T factor, const Point2D& point) {
    return Point2D(factor * point.x, factor * point.y);
  }

  // sign operators:
  inline constexpr Point2D operator+() const {
    return *this;
  }
  inline constexpr Point2D operator-() const {
    return Point2D(-x, -y);
  }

  // comfort:
  [[nodiscard]] inline constexpr bool isNull() const {
    return Math::isNull(x) and Math::isNull(y);
  }
  inline constexpr void transpose() {
    std::swap(x, y);
  }
  inline constexpr Point2D transposed() const {
    return Point2D{y, x};
  }
  inline constexpr void swap(Point2D& other) noexcept {
    std::swap(x, other.x);
    std::swap(y, other.y);
  }
  template <class U>
  inline constexpr explicit operator Point2D<U>() const {
    return Point2D<U>(static_cast<U>(x), static_cast<U>(y));
  }
  inline constexpr std::pair<T, T> toPair() const {
    return std::make_pair(x, y);
  }
  template <class U, class V = U>
  inline constexpr std::pair<U, V> toPair() const {
    return std::make_pair(static_cast<U>(x), static_cast<V>(y));
  }
  [[nodiscard]] inline constexpr QPoint toQPoint() const {
    using QPointCoordType = std::common_type_t<decltype(std::declval<QPoint>().x()),
                                               decltype(std::declval<QPoint>().y())>;
    return QPoint{static_cast<QPointCoordType>(x), static_cast<QPointCoordType>(y)};
  }
  [[nodiscard]] inline constexpr QPointF toQPointF() const {
    using QPointFCoordType = std::common_type_t<decltype(std::declval<QPointF>().x()),
                                                decltype(std::declval<QPointF>().y())>;
    return QPointF{static_cast<QPointFCoordType>(x), static_cast<QPointFCoordType>(y)};
  }
  inline constexpr T& operator[](int i) {
    if (0 <= i and i < 2) {
      return *reinterpret_cast<T*>(this + i);
    }
    qFatal("operator[](%d): index out of range", i);
  }
  inline constexpr T operator[](int i) const {
    if (0 <= i and i < 2) {
      return *reinterpret_cast<T*>(this + i);
    }
    qFatal("operator[](%d): index out of range", i);
  }
  inline constexpr T manhattanLength() const {
    return std::abs(x) + std::abs(y);
  }
  inline constexpr T dot(const Point2D& other) const {
    return x * other.x + y * other.y;
  }
  inline constexpr T cross(const Point2D& other) const {
    return x * other.y - y * other.x;
  }
  inline constexpr T distSquaredTo(const Point2D& other) const {
    return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
  }
  inline constexpr auto distTo(const Point2D& other) const {
    return std::sqrt(distSquaredTo(other));
  }
  inline constexpr auto distToLine(const Point2D& a, const Point2D& b) const
      requires(std::floating_point<T>) {
    const auto projected = projectedOntoLine(a, b);
    return distTo(projected);
  }
  inline constexpr auto distToSegment(const Point2D& a, const Point2D& b) const
      requires(std::floating_point<T>) {
    const auto projected = projectedOntoSegment(a, b);
    return distTo(projected);
  }
  inline constexpr void rotateCW90() {
    std::swap(x, y), y = -y;
  }
  inline constexpr Point2D rotatedCW90() const {
    Point2D result{*this};
    result.rotateCW90();
    return result;
  }
  inline constexpr void rotateCCW90() {
    std::swap(x, y), x = -x;
  }
  inline constexpr Point2D rotatedCCW90() const {
    Point2D result{*this};
    result.rotateCCW90();
    return result;
  }
  inline constexpr void rotateCW(T t) requires(std::floating_point<T>) {
    const auto cos = std::cos(t);
    const auto sin = std::sin(t);

    const auto rx = x * cos + y * sin;
    const auto ry = -x * sin + y * cos;

    x = rx, y = ry;
  }
  inline constexpr Point2D rotatedCW(T t) const requires(std::floating_point<T>) {
    Point2D result{*this};
    result.rotateCW(t);
    return result;
  }
  inline constexpr void rotateCCW(T t) requires(std::floating_point<T>) {
    const auto cos = std::cos(t);
    const auto sin = std::sin(t);

    const auto rx = x * cos - y * sin;
    const auto ry = x * sin + y * cos;

    x = rx, y = ry;
  }
  inline constexpr Point2D rotatedCCW(T t) const requires(std::floating_point<T>) {
    Point2D result{*this};
    result.rotateCCW(t);
    return result;
  }
  inline constexpr auto angle() const {
    return std::atan2(y, x);
  }
  inline constexpr auto angleTo(const Point2D& other) const {
    return std::atan2(cross(other), dot(other));
  }
  inline constexpr T lengthSquared() const {
    return dot(*this);
  }
  inline constexpr auto length() const {
    return std::sqrt(lengthSquared());
  }
  inline constexpr auto norm() const {
    return std::sqrt(lengthSquared());
  }
  inline constexpr void resize(T t) requires(std::floating_point<T>) {
    if (auto norm = this->norm(); not Math::isNull(norm)) {
      x *= t / norm, y *= t / norm;
    }
  }
  inline constexpr Point2D resized(T t) const requires(std::floating_point<T>) {
    Point2D result{*this};
    result.resize(t);
    return result;
  }
  inline constexpr void normalize() requires(std::floating_point<T>) {
    if (auto norm = this->norm(); not Math::isNull(norm)) {
      x /= norm, y /= norm;
    }
  }
  inline constexpr Point2D normalized() const requires(std::floating_point<T>) {
    Point2D result{*this};
    result.normalize();
    return result;
  }
  inline constexpr void normalize() requires(std::integral<T>) {
    if (auto gcd = std::gcd(std::abs(x), std::abs(y)); static_cast<bool>(gcd)) {
      x /= gcd, y /= gcd;
    }
  }
  inline constexpr Point2D normalized() const requires(std::integral<T>) {
    Point2D result{*this};
    result.normalize();
    return result;
  }
  inline constexpr void unitaryAxisNormalize() {
    x = Math::isNull(x) ? 0 : (x > 0) ? 1 : -1, y = Math::isNull(y) ? 0 : (y > 0) ? 1 : -1;
  }
  inline constexpr Point2D unitaryAxisNormalized() const {
    Point2D result{*this};
    result.unitaryAxisNormalize();
    return result;
  }
  inline constexpr void projectOntoLine(const Point2D& a,
                                        const Point2D& b) requires(std::floating_point<T>) {
    if (a == b) {
      qFatal("projectOntoLine: a == b");
    }
    const Point2D ab = b - a;
    *this = a + ab * ab.dot(*this - a) / ab.dot(ab);
  }
  inline constexpr Point2D projectedOntoLine(const Point2D& a, const Point2D& b) const
      requires(std::floating_point<T>) {
    Point2D result{*this};
    result.projectOntoLine(a, b);
    return result;
  }
  inline constexpr void projectOntoSegment(const Point2D& a,
                                           const Point2D& b) requires(std::floating_point<T>) {
    if (a == b) {
      qFatal("projectOntoSegment: a == b");
    }
    const auto ab = b - a;
    auto r = ab.dot(ab);
    if (Math::isNull(r)) {
      *this = a;
    } else {
      r = (*this - a).dot(ab) / r;
      if (r < 0) {
        *this = a;
      } else if (r > 1) {
        *this = b;
      } else {
        *this = a + ab * r;
      }
    }
  }
  inline constexpr Point2D projectedOntoSegment(const Point2D& a, const Point2D& b) const
      requires(std::floating_point<T>) {
    Point2D result{*this};
    result.projectOntoSegment(a, b);
    return result;
  }
  inline constexpr void reflectOntoLine(const Point2D& a,
                                        const Point2D& b) requires(std::floating_point<T>) {
    if (a == b) {
      qFatal("reflectOntoLine: a == b");
    }
    *this = static_cast<T>(2) * projectedOntoLine(a, b) - *this;
  }
  inline constexpr Point2D reflectedOntoLine(const Point2D& a, const Point2D& b) const
      requires(std::floating_point<T>) {
    Point2D result{*this};
    result.reflectOntoLine(a, b);
    return result;
  }
  inline constexpr bool isOnTheLeftOf(const Point2D& a, const Point2D& b) const {
    return (b - a).cross(*this - a) > 0;
  }
  inline constexpr bool isOnTheRightOf(const Point2D& a, const Point2D& b) const {
    return (b - a).cross(*this - a) < 0;
  }
  inline constexpr bool isInPolygon(const QVector<Point2D>& polygon) const {
    int n = static_cast<int>(polygon.size());
    bool c = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
      if ((polygon[i].y <= y and y < polygon[j].y) or (polygon[j].y <= y and y < polygon[i].y)) {
        if (x < (polygon[i].x + (polygon[j].x - polygon[i].x) * (y - polygon[i].y) /
                                    (polygon[j].y - polygon[i].y))) {
          c = !c;
        }
      }
    }
    return c;
  }
  inline constexpr bool isOnPolygon(const QVector<Point2D>& polygon) const {
    int n = static_cast<int>(polygon.size());
    for (int i = 0; i < n; ++i) {
      if (auto proj = projectedOntoSegment(polygon[i], polygon[(i + 1) % n]);
          Math::isNull(distSquaredTo(proj))) {
        return true;
      }
    }
    return false;
  }

  // streams:
  friend inline std::istream& operator>>(std::istream& is, Point2D& point) {
    return is >> point.x >> point.y;
  }
  friend inline std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << '(' << point.x << ", " << point.y << ')';
    return os;
  }

  friend inline constexpr std::size_t qHash(const Point2D& point, std::size_t seed = 0) {
    return qHashMulti(seed, point.x, point.y);
  }
};

#ifndef QT_NO_DEBUG_STREAM
template <class T>
QDebug operator<<(QDebug dbg, const Point2D<T>& point) {
  QDebugStateSaver saver(dbg);
  dbg.nospace() << "Point2D(" << point.x << ',' << point.y << ')';
  return dbg;
}
#endif

namespace std {
  template <class T>
  struct hash<Point2D<T>> {
    constexpr size_t operator()(const Point2D<T>& point) const noexcept {
      const auto hash = std::hash<T>{};

      size_t h1 = hash(point.x);
      size_t h2 = hash(point.y);

      return h1 ^ (h2 << 1ul);
    }
  };
} // namespace std

#endif // SOCCER_COMMON_POINT2D_H
