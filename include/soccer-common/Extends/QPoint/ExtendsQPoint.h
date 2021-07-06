#ifndef SOCCER_COMMON_EXTENDSPOINT_H
#define SOCCER_COMMON_EXTENDSPOINT_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "google-explicit-constructor"

#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Extends/Detail/ExtendsDetail.h"

template <>
class Extends<QPoint> : public QPoint {
  using CoordType = Geometry2D::CoordType<QPoint>;

 public:
  constexpr Extends() noexcept : QPoint() {
  }
  constexpr Extends(const QPoint& p) noexcept : QPoint(p) {
  }
  constexpr Extends(CoordType xpos, CoordType ypos) noexcept : QPoint(xpos, ypos) {
  }

  constexpr inline bool operator<(const Extends<QPoint>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) < static_cast<const QPoint&>(other);
  }
  constexpr inline bool operator<(const QPoint& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) < other;
  }
  friend constexpr inline bool operator<(const QPoint& lhs, const Extends<QPoint>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPoint&>(rhs);
  }

  constexpr inline Extends<QPoint>& operator+=(const Extends<QPoint>& point) {
    QPoint::operator+=(static_cast<const QPoint&>(point));
    return *this;
  }
  constexpr inline Extends<QPoint>& operator-=(const Extends<QPoint>& point) {
    QPoint::operator-=(static_cast<const QPoint&>(point));
    return *this;
  }
  constexpr inline Extends<QPoint>& operator*=(float factor) {
    QPoint::operator*=(factor);
    return *this;
  }
  constexpr inline Extends<QPoint>& operator*=(double factor) {
    QPoint::operator*=(factor);
    return *this;
  }
  constexpr inline Extends<QPoint>& operator*=(int factor) {
    QPoint::operator*=(factor);
    return *this;
  }
  constexpr inline Extends<QPoint>& operator/=(qreal divisor) {
    QPoint::operator/=(divisor);
    return *this;
  }

  friend constexpr inline Extends<QPoint> operator+(const Extends<QPoint>& p1,
                                                    const Extends<QPoint>& p2) noexcept {
    return Extends<QPoint>(static_cast<const QPoint&>(p1) + static_cast<const QPoint&>(p2));
  }
  friend constexpr inline Extends<QPoint> operator-(const Extends<QPoint>& p1,
                                                    const Extends<QPoint>& p2) noexcept {
    return Extends<QPoint>(static_cast<const QPoint&>(p1) - static_cast<const QPoint&>(p2));
  }
  friend constexpr inline Extends<QPoint> operator*(const Extends<QPoint>& p, float factor) {
    return Extends<QPoint>(static_cast<const QPoint&>(p) * factor);
  }
  friend constexpr inline Extends<QPoint> operator*(const Extends<QPoint>& p, double factor) {
    return Extends<QPoint>(static_cast<const QPoint&>(p) * factor);
  }
  friend constexpr inline Extends<QPoint> operator*(const Extends<QPoint>& p, int factor) noexcept {
    return Extends<QPoint>(static_cast<const QPoint&>(p) * factor);
  }
  friend constexpr inline Extends<QPoint> operator*(float factor, const Extends<QPoint>& p) {
    return Extends<QPoint>(factor * static_cast<const QPoint&>(p));
  }
  friend constexpr inline Extends<QPoint> operator*(double factor, const Extends<QPoint>& p) {
    return Extends<QPoint>(factor * static_cast<const QPoint&>(p));
  }
  friend constexpr inline Extends<QPoint> operator*(int factor, const Extends<QPoint>& p) noexcept {
    return Extends<QPoint>(factor * static_cast<const QPoint&>(p));
  }
  friend constexpr inline Extends<QPoint> operator+(const Extends<QPoint>& p) noexcept {
    return Extends<QPoint>(p);
  }
  friend constexpr inline Extends<QPoint> operator-(const Extends<QPoint>& p) noexcept {
    return Extends<QPoint>(-static_cast<const QPoint&>(p));
  }
  friend constexpr inline Extends<QPoint> operator/(const Extends<QPoint>& p, qreal c) {
    return Extends<QPoint>(static_cast<const QPoint&>(p) / c);
  }

  constexpr inline void transpose() {
    *this = transposed();
  }

  constexpr inline CoordType& operator[](qsizetype i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline CoordType operator[](qsizetype i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline CoordType dot(const QPoint& other) const {
    return Geometry2D::dot<QPoint>(*this, other);
  }

  constexpr inline CoordType cross(const QPoint& other) const {
    return Geometry2D::cross<QPoint>(*this, other);
  }

  constexpr inline CoordType distSquaredTo(const QPoint& other) const {
    return Geometry2D::distanceSquared<QPoint>(*this, other);
  }

  constexpr inline auto distTo(const QPoint& other) const {
    return Geometry2D::distance<QPoint>(*this, other);
  }

  constexpr inline void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  constexpr inline Extends<QPoint> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  constexpr inline void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  constexpr inline Extends<QPoint> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  constexpr inline auto angle() const {
    return Geometry2D::angle(*this);
  }

  constexpr inline auto angleTo(const QPoint& other) const {
    return Geometry2D::angleBetween<QPoint>(*this, other);
  }

  constexpr inline CoordType lengthSquared() const {
    return Geometry2D::lengthSquared(*this);
  }

  constexpr inline auto length() const {
    return Geometry2D::length(*this);
  }

  using QPoint::manhattanLength;

  constexpr inline void normalize() {
    *this = Geometry2D::normalize(*this);
  }

  constexpr inline Extends<QPoint> normalized() const {
    return Geometry2D::normalize(*this);
  }

  inline bool isInPolygon(const QVector<QPoint>& polygon) const {
    return Geometry2D::pointInPolygon<QPoint>(polygon, *this);
  }

 private:
  using QPoint::dotProduct;
};

template <>
class Extends<QPointF> : public QPointF {
  using CoordType = Geometry2D::CoordType<QPointF>;

 public:
  constexpr Extends() noexcept : QPointF() {
  }
  constexpr Extends(const QPoint& p) noexcept : QPointF(p) {
  }
  constexpr Extends(const QPointF& p) noexcept : QPointF(p) {
  }
  constexpr Extends(CoordType xpos, CoordType ypos) noexcept : QPointF(xpos, ypos) {
  }

  constexpr inline bool operator<(const Extends<QPointF>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < static_cast<const QPointF&>(other);
  }

  constexpr inline bool operator<(const QPointF& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < other;
  }

  friend constexpr inline bool operator<(const QPointF& lhs, const Extends<QPointF>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPointF&>(rhs);
  }

  constexpr inline Extends<QPointF>& operator+=(const Extends<QPointF>& p) {
    QPointF::operator+=(static_cast<const QPointF&>(p));
    return *this;
  }
  constexpr inline Extends<QPointF>& operator-=(const Extends<QPointF>& p) {
    QPointF::operator-=(static_cast<const QPointF&>(p));
    return *this;
  }
  constexpr inline Extends<QPointF>& operator*=(qreal c) {
    QPointF::operator*=(c);
    return *this;
  }
  constexpr inline Extends<QPointF>& operator/=(qreal c) {
    QPointF::operator/=(c);
    return *this;
  }

  friend constexpr inline Extends<QPointF> operator+(const Extends<QPointF>& p1,
                                                     const Extends<QPointF>& p2) {
    return Extends<QPointF>(static_cast<const QPointF&>(p1) + static_cast<const QPointF&>(p2));
  }
  friend constexpr inline Extends<QPointF> operator-(const Extends<QPointF>& p1,
                                                     const Extends<QPointF>& p2) {
    return Extends<QPointF>(static_cast<const QPointF&>(p1) - static_cast<const QPointF&>(p2));
  }
  friend constexpr inline Extends<QPointF> operator*(const Extends<QPointF>& p, qreal c) {
    return Extends<QPointF>(static_cast<const QPointF&>(p) * c);
  }
  friend constexpr inline Extends<QPointF> operator*(qreal c, const Extends<QPointF>& p) {
    return Extends<QPointF>(c * static_cast<const QPointF&>(p));
  }
  friend constexpr inline Extends<QPointF> operator+(const Extends<QPointF>& p) {
    return Extends<QPointF>(p);
  }
  friend constexpr inline Extends<QPointF> operator-(const Extends<QPointF>& p) {
    return Extends<QPointF>(-static_cast<const QPointF&>(p));
  }
  friend constexpr inline Extends<QPointF> operator/(const Extends<QPointF>& p, qreal divisor) {
    return Extends<QPointF>(static_cast<const QPointF&>(p) / divisor);
  }

  constexpr inline void transpose() {
    *this = transposed();
  }

  constexpr inline CoordType& operator[](qsizetype i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline CoordType operator[](qsizetype i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline CoordType dot(const QPointF& other) const {
    return Geometry2D::dot<QPointF>(*this, other);
  }

  constexpr inline CoordType cross(const QPointF& other) const {
    return Geometry2D::cross<QPointF>(*this, other);
  }

  constexpr inline CoordType distSquaredTo(const QPointF& other) const {
    return Geometry2D::distanceSquared<QPointF>(*this, other);
  }

  constexpr inline auto distTo(const QPointF& other) const {
    return Geometry2D::distance<QPointF>(*this, other);
  }

  constexpr inline auto distToLine(const QPointF& a, const QPointF& b) const {
    return Geometry2D::distancePointLine<QPointF>(a, b, *this);
  }

  constexpr inline auto distToLine(const QLineF& line) const {
    return Geometry2D::distancePointLine<QPointF>(line, *this);
  }

  constexpr inline auto distToSegment(const QPointF& a, const QPointF& b) const {
    return Geometry2D::distancePointSegment<QPointF>(a, b, *this);
  }

  constexpr inline auto distToSegment(const QLineF& line) const {
    return Geometry2D::distancePointSegment<QPointF>(line, *this);
  }

  constexpr inline Extends<QPointF> projectedOntoLine(const QPointF& a, const QPointF& b) const {
    return Geometry2D::projectPointLine<QPointF>(a, b, *this);
  }

  constexpr inline Extends<QPointF> projectedOntoLine(const QLineF& line) const {
    return Geometry2D::projectPointLine<QPointF>(line.p1(), line.p2(), *this);
  }

  constexpr inline Extends<QPointF> projectedOntoSegment(const QPointF& a, const QPointF& b) const {
    return Geometry2D::projectPointSegment<QPointF>(a, b, *this);
  }

  constexpr inline Extends<QPointF> projectedOntoSegment(const QLineF& line) const {
    return Geometry2D::projectPointSegment<QPointF>(line.p1(), line.p2(), *this);
  }

  constexpr inline void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  constexpr inline Extends<QPointF> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  constexpr inline void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  constexpr inline Extends<QPointF> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  constexpr inline void rotateCCW(CoordType t) {
    *this = Geometry2D::rotateCCW(*this, t);
  }

  constexpr inline Extends<QPointF> rotatedCCW(CoordType t) const {
    return Geometry2D::rotateCCW(*this, t);
  }

  constexpr inline auto angle() const {
    return Geometry2D::angle(*this);
  }

  constexpr inline auto angleTo(const QPointF& other) const {
    return Geometry2D::angleBetween<QPointF>(*this, other);
  }

  constexpr inline CoordType lengthSquared() const {
    return Geometry2D::lengthSquared(*this);
  }

  constexpr inline auto length() const {
    return Geometry2D::length(*this);
  }

  using QPointF::manhattanLength;

  constexpr inline void resize(CoordType t) {
    *this = Geometry2D::resize(*this, t);
  }

  constexpr inline Extends<QPointF> resized(CoordType t) const {
    return Geometry2D::resize(*this, t);
  }

  constexpr inline void normalize() {
    *this = Geometry2D::normalize(*this);
  }

  constexpr inline Extends<QPointF> normalized() const {
    return Geometry2D::normalize(*this);
  }

  inline bool isInPolygon(const QVector<QPointF>& polygon) const {
    return Geometry2D::pointInPolygon<QPointF>(polygon, *this);
  }

  inline bool isOnPolygon(const QVector<QPointF>& polygon) const {
    return Geometry2D::pointOnPolygon<QPointF>(polygon, *this);
  }

 private:
  using QPointF::dotProduct;
};

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_EXTENDSPOINT_H
