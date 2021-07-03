#ifndef SOCCER_COMMON_EXTENDSPOINT_H
#define SOCCER_COMMON_EXTENDSPOINT_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "google-explicit-constructor"

#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Extends/Detail/ExtendsDetail.h"

template <>
class Extends<QPoint> : public QPoint {
 public:
  constexpr Extends() noexcept : QPoint() {
  }
  constexpr Extends(const QPoint& p) noexcept : QPoint(p) {
  }
  constexpr Extends(int xpos, int ypos) noexcept : QPoint(xpos, ypos) {
  }

  constexpr bool operator<(const Extends<QPoint>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) < static_cast<const QPoint&>(other);
  }

  constexpr bool operator<(const QPoint& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) < other;
  }

  friend constexpr bool operator<(const QPoint& lhs, const Extends<QPoint>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPoint&>(rhs);
  }

  constexpr void transpose() {
    *this = transposed();
  }

  constexpr inline int& operator[](int i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline int operator[](int i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr int dot(const QPoint& other) const {
    return Geometry2D::dot<QPoint>(*this, other);
  }

  constexpr int cross(const QPoint& other) const {
    return Geometry2D::cross<QPoint>(*this, other);
  }

  constexpr int distSquaredTo(const QPoint& other) const {
    return Geometry2D::distanceSquared<QPoint>(*this, other);
  }

  constexpr qreal distTo(const QPoint& other) const {
    return Geometry2D::distance<QPoint>(*this, other);
  }

  constexpr void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  constexpr Extends<QPoint> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  constexpr void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  constexpr Extends<QPoint> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  constexpr qreal angle() const {
    return Geometry2D::angle(*this);
  }

  constexpr qreal angleTo(const QPoint& other) const {
    return Geometry2D::angleBetween<QPoint>(*this, other);
  }

  constexpr int lengthSquared() const {
    return Geometry2D::lengthSquared(*this);
  }

  constexpr qreal length() const {
    return Geometry2D::length(*this);
  }

  using QPoint::manhattanLength;

  constexpr void normalize() {
    *this = Geometry2D::normalize(*this);
  }

  constexpr Extends<QPoint> normalized() const {
    return Geometry2D::normalize(*this);
  }

  bool isInPolygon(const QVector<QPoint>& polygon) const {
    return Geometry2D::pointInPolygon<QPoint>(polygon, *this);
  }
};

template <>
class Extends<QPointF> : public QPointF {
 public:
  constexpr Extends() noexcept : QPointF() {
  }
  constexpr Extends(const QPoint& p) noexcept : QPointF(p) {
  }
  constexpr Extends(const QPointF& p) noexcept : QPointF(p) {
  }
  constexpr Extends(qreal xpos, qreal ypos) noexcept : QPointF(xpos, ypos) {
  }

  constexpr bool operator<(const Extends<QPointF>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < static_cast<const QPointF&>(other);
  }

  constexpr bool operator<(const QPointF& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < other;
  }

  friend constexpr bool operator<(const QPointF& lhs, const Extends<QPointF>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPointF&>(rhs);
  }

  constexpr void transpose() {
    *this = transposed();
  }

  constexpr inline qreal& operator[](int i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr inline qreal operator[](int i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  constexpr qreal dot(const QPointF& other) const {
    return Geometry2D::dot<QPointF>(*this, other);
  }

  constexpr qreal cross(const QPointF& other) const {
    return Geometry2D::cross<QPointF>(*this, other);
  }

  constexpr qreal distSquaredTo(const QPointF& other) const {
    return Geometry2D::distanceSquared<QPointF>(*this, other);
  }

  constexpr qreal distTo(const QPointF& other) const {
    return Geometry2D::distance<QPointF>(*this, other);
  }

  constexpr qreal distToLine(const QPointF& a, const QPointF& b) const {
    return Geometry2D::distancePointLine<QPointF>(a, b, *this);
  }

  constexpr qreal distToLine(const QLineF& line) const {
    return Geometry2D::distancePointLine<QPointF>(line, *this);
  }

  constexpr qreal distToSegment(const QPointF& a, const QPointF& b) const {
    return Geometry2D::distancePointSegment<QPointF>(a, b, *this);
  }

  constexpr qreal distToSegment(const QLineF& line) const {
    return Geometry2D::distancePointSegment<QPointF>(line, *this);
  }

  constexpr Extends<QPointF> projectedOntoLine(const QPointF& a, const QPointF& b) const {
    return Geometry2D::projectPointLine<QPointF>(a, b, *this);
  }

  constexpr Extends<QPointF> projectedOntoLine(const QLineF& line) const {
    return Geometry2D::projectPointLine<QPointF>(line.p1(), line.p2(), *this);
  }

  constexpr Extends<QPointF> projectedOntoSegment(const QPointF& a, const QPointF& b) const {
    return Geometry2D::projectPointSegment<QPointF>(a, b, *this);
  }

  constexpr Extends<QPointF> projectedOntoSegment(const QLineF& line) const {
    return Geometry2D::projectPointSegment<QPointF>(line.p1(), line.p2(), *this);
  }

  constexpr void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  constexpr Extends<QPointF> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  constexpr void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  constexpr Extends<QPointF> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  constexpr void rotateCCW(qreal t) {
    *this = Geometry2D::rotateCCW(*this, t);
  }

  constexpr Extends<QPointF> rotatedCCW(qreal t) const {
    return Geometry2D::rotateCCW(*this, t);
  }

  constexpr qreal angle() const {
    return Geometry2D::angle(*this);
  }

  constexpr qreal angleTo(const QPointF& other) const {
    return Geometry2D::angleBetween<QPointF>(*this, other);
  }

  constexpr qreal lengthSquared() const {
    return Geometry2D::lengthSquared(*this);
  }

  constexpr qreal length() const {
    return Geometry2D::length(*this);
  }

  using QPointF::manhattanLength;

  constexpr void resize(qreal t) {
    *this = Geometry2D::resize(*this, t);
  }

  constexpr Extends<QPointF> resized(qreal t) const {
    return Geometry2D::resize(*this, t);
  }

  constexpr void normalize() {
    *this = Geometry2D::normalize(*this);
  }

  constexpr Extends<QPointF> normalized() const {
    return Geometry2D::normalize(*this);
  }

  inline bool isInPolygon(const QVector<QPointF>& polygon) const {
    return Geometry2D::pointInPolygon<QPointF>(polygon, *this);
  }

  inline bool isOnPolygon(const QVector<QPointF>& polygon) const {
    return Geometry2D::pointOnPolygon<QPointF>(polygon, *this);
  }
};

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_EXTENDSPOINT_H
