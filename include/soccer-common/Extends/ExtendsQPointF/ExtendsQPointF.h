#ifndef EXTENDSQPOINTF_H
#define EXTENDSQPOINTF_H

#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Extends/detail/ExtendsImpl.h"

template <>
class Extends<QPointF> : public QPointF {
 public:
  template <class... Args>
  Extends(Args&&... args) : QPointF(std::forward<Args>(args)...) {
  }

  decltype(auto) operator<(const Extends<QPointF>& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) <
           static_cast<const QPointF&>(other);
  }

  decltype(auto) operator<(const QPointF& other) const {
    using Geometry2D::operator<;
    return static_cast<const QPointF&>(*this) < other;
  }

  friend decltype(auto) operator<(const QPointF& lhs,
                                  const Extends<QPointF>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const QPointF&>(rhs);
  }

  decltype(auto) operator[](int i) {
    switch (i) {
      case 0: return rx();
      case 1: return ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  decltype(auto) operator[](int i) const {
    switch (i) {
      case 0: return x();
      case 1: return y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  decltype(auto) dot(const QPointF& other) const {
    return Geometry2D::dot<QPointF>(*this, other);
  }

  decltype(auto) cross(const QPointF& other) const {
    return Geometry2D::cross<QPointF>(*this, other);
  }

  decltype(auto) distSquare(const QPointF& other) const {
    return Geometry2D::distanceSquare<QPointF>(*this, other);
  }

  decltype(auto) dist(const QPointF& other) const {
    return Geometry2D::distance<QPointF>(*this, other);
  }

  decltype(auto) rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  decltype(auto) rotatedCW90() const {
    return Extends<QPointF>(Geometry2D::rotateCW90(*this));
  }

  decltype(auto) rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  decltype(auto) rotatedCCW90() const {
    return Extends<QPointF>(Geometry2D::rotateCCW90(*this));
  }

  decltype(auto) rotateCCW(qreal t) {
    *this = Geometry2D::rotateCCW(*this, t);
  }

  decltype(auto) rotatedCCW(qreal t) const {
    return Extends<QPointF>(Geometry2D::rotateCCW(*this, t));
  }

  decltype(auto) angle() const {
    return Geometry2D::angle(*this);
  }

  decltype(auto) angleBetween(const QPointF& other) const {
    return Geometry2D::angleBetween<QPointF>(*this, other);
  }

  decltype(auto) length() const {
    return Geometry2D::length(*this);
  }

  decltype(auto) resize(qreal t) {
    *this = Geometry2D::resize(*this, t);
  }

  decltype(auto) resized(qreal t) const {
    return Extends<QPointF>(Geometry2D::resize(*this, t));
  }

  decltype(auto) normalize() {
    *this = Geometry2D::normalize(*this);
  }

  decltype(auto) normalized() const {
    return Extends<QPointF>(Geometry2D::normalize(*this));
  }
};

#endif // EXTENDSQPOINTF_H
