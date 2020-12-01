#ifndef EXTENDSPOINT_H
#define EXTENDSPOINT_H

#include "soccer-common/Geometry/Geometry.h"
#include "soccer-common/Extends/detail/ExtendsImpl.h"

template <class PT>
class Extends<PT, detail::enable_if_any_t<PT, QPoint, QPointF>> : public PT {
 public:
  template <class... Args>
  Extends(Args&&... args) : PT(std::forward<Args>(args)...) {
  }

  decltype(auto) operator<(const Extends<PT>& other) const {
    using Geometry2D::operator<;
    return static_cast<const PT&>(*this) < static_cast<const PT&>(other);
  }

  decltype(auto) operator<(const PT& other) const {
    using Geometry2D::operator<;
    return static_cast<const PT&>(*this) < other;
  }

  friend decltype(auto) operator<(const PT& lhs, const Extends<PT>& rhs) {
    using Geometry2D::operator<;
    return lhs < static_cast<const PT&>(rhs);
  }

  decltype(auto) operator[](int i) {
    switch (i) {
      case 0: return PT::rx();
      case 1: return PT::ry();
      default: throw std::out_of_range("index out of range.");
    }
  }

  decltype(auto) operator[](int i) const {
    switch (i) {
      case 0: return PT::x();
      case 1: return PT::y();
      default: throw std::out_of_range("index out of range.");
    }
  }

  decltype(auto) dot(const PT& other) const {
    return Geometry2D::dot<PT>(*this, other);
  }

  decltype(auto) cross(const PT& other) const {
    return Geometry2D::cross<PT>(*this, other);
  }

  decltype(auto) distSquared(const PT& other) const {
    return Geometry2D::distanceSquared<PT>(*this, other);
  }

  decltype(auto) dist(const PT& other) const {
    return Geometry2D::distance<PT>(*this, other);
  }

  decltype(auto) rotateCW90() {
    *this = Geometry2D::rotateCW90(*this);
  }

  decltype(auto) rotatedCW90() const {
    return Extends<PT>(Geometry2D::rotateCW90(*this));
  }

  decltype(auto) rotateCCW90() {
    *this = Geometry2D::rotateCCW90(*this);
  }

  decltype(auto) rotatedCCW90() const {
    return Extends<PT>(Geometry2D::rotateCCW90(*this));
  }

  decltype(auto) rotateCCW(qreal t) {
    *this = Geometry2D::rotateCCW(*this, t);
  }

  decltype(auto) rotatedCCW(qreal t) const {
    return Extends<PT>(Geometry2D::rotateCCW(*this, t));
  }

  decltype(auto) angle() const {
    return Geometry2D::angle(*this);
  }

  decltype(auto) angleTo(const PT& other) const {
    return Geometry2D::angleBetween<PT>(*this, other);
  }

  decltype(auto) length() const {
    return Geometry2D::length(*this);
  }

  decltype(auto) resize(qreal t) {
    *this = Geometry2D::resize(*this, t);
  }

  decltype(auto) resized(qreal t) const {
    return Extends<PT>(Geometry2D::resize(*this, t));
  }

  decltype(auto) normalize() {
    *this = Geometry2D::normalize(*this);
  }

  decltype(auto) normalized() const {
    return Extends<PT>(Geometry2D::normalize(*this));
  }
};

#endif // EXTENDSPOINT_H
