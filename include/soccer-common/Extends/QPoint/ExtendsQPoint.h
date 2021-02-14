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
  template <class... Args>
  Extends(Args&&... args) : QPoint(std::forward<Args>(args)...) {
  }

  inline bool operator<(const Extends<QPoint>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) <
           static_cast<const QPoint&>(other);
  }

  inline bool operator<(const QPoint& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPoint&>(*this) < other;
  }

  friend inline bool operator<(const QPoint& lhs, const Extends<QPoint>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPoint&>(rhs);
  }

  inline int& operator[](int i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  inline int operator[](int i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  int dot(const QPoint& other) const {
    return Geometry2D::dot<QPoint>(*this, other);
  }

  int cross(const QPoint& other) const {
    return Geometry2D::cross<QPoint>(*this, other);
  }

  int distSquaredTo(const QPoint& other) const {
    return Geometry2D::distanceSquared<QPoint>(*this, other);
  }

  qreal distTo(const QPoint& other) const {
    return Geometry2D::distance<QPoint>(*this, other);
  }

  void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  Extends<QPoint> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  Extends<QPoint> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  qreal angle() const {
    return Geometry2D::angle(*this);
  }

  qreal angleTo(const QPoint& other) const {
    return Geometry2D::angleBetween<QPoint>(*this, other);
  }

  qreal length() const {
    return Geometry2D::length(*this);
  }

  using QPoint::manhattanLength;
};

template <>
class Extends<QPointF> : public QPointF {
 public:
  template <class... Args>
  Extends(Args&&... args) : QPointF(std::forward<Args>(args)...) {
  }

  inline bool operator<(const Extends<QPointF>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) <
           static_cast<const QPointF&>(other);
  }

  inline bool operator<(const QPointF& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < other;
  }

  friend inline bool operator<(const QPointF& lhs,
                               const Extends<QPointF>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPointF&>(rhs);
  }

  inline qreal& operator[](int i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  inline qreal operator[](int i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  qreal dot(const QPointF& other) const {
    return Geometry2D::dot<QPointF>(*this, other);
  }

  qreal cross(const QPointF& other) const {
    return Geometry2D::cross<QPointF>(*this, other);
  }

  qreal distSquaredTo(const QPointF& other) const {
    return Geometry2D::distanceSquared<QPointF>(*this, other);
  }

  qreal distTo(const QPointF& other) const {
    return Geometry2D::distance<QPointF>(*this, other);
  }

  void rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  Extends<QPointF> rotatedCW90() const {
    return Geometry2D::rotateCW90(*this);
  }

  void rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  Extends<QPointF> rotatedCCW90() const {
    return Geometry2D::rotateCCW90(*this);
  }

  void rotateCCW(qreal t) {
    *this = Geometry2D::rotateCCW(*this, t);
  }

  Extends<QPointF> rotatedCCW(qreal t) const {
    return Geometry2D::rotateCCW(*this, t);
  }

  qreal angle() const {
    return Geometry2D::angle(*this);
  }

  qreal angleTo(const QPointF& other) const {
    return Geometry2D::angleBetween<QPointF>(*this, other);
  }

  qreal length() const {
    return Geometry2D::length(*this);
  }

  using QPointF::manhattanLength;

  void resize(qreal t) {
    *this = Geometry2D::resize(*this, t);
  }

  Extends<QPointF> resized(qreal t) const {
    return Geometry2D::resize(*this, t);
  }

  void normalize() {
    *this = Geometry2D::normalize(*this);
  }

  Extends<QPointF> normalized() const {
    return Geometry2D::normalize(*this);
  }
};

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_EXTENDSPOINT_H