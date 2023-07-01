#ifndef SOCCER_COMMON_PAINTERGEOMETRY_H
#define SOCCER_COMMON_PAINTERGEOMETRY_H

#include <QPointF>
#include <QPoint>
#include <QPolygonF>
#include <QVector>
#include <QVector2D>
#include <QVector3D>

struct Vertex : public QPointF {
    constexpr Vertex() : QPointF() {
    }
    constexpr Vertex(qreal x, qreal y) : QPointF(x, y) {
    }
    constexpr Vertex(const QPoint& p) : QPointF(p) {
    }
    constexpr Vertex(const QPointF& p) : QPointF(p) {
    }
    constexpr Vertex(const QVector2D& v) : QPointF(v.x(), v.y()) {
    }
    constexpr Vertex(const QVector3D& v) : QPointF(v.x(), v.y()) {
    }
    template <class U, class V>
    constexpr Vertex(const std::pair<U, V>& p) : QPointF(p.first, p.second) {
    }

    friend constexpr bool operator==(const Vertex& lhs, const Vertex& rhs) {
      return qFuzzyCompare(lhs.x(), rhs.x()) && qFuzzyCompare(lhs.y(), rhs.y());
    }
  };

  struct Polygon : public QVector<Vertex> {
    inline Polygon() : QVector<Vertex>() {
    }
    inline Polygon(const QVector<Vertex>& polygon) : QVector<Vertex>(polygon) {
    }
    inline Polygon(const QVector<QPoint>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QPointF>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QVector2D>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    inline Polygon(const QVector<QVector3D>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class U, class V>
    inline Polygon(const QVector<std::pair<U, V>>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class U>
    inline Polygon(const std::initializer_list<U>& polygon) :
        QVector<Vertex>(polygon.begin(), polygon.end()) {
    }
    template <class PT>
    inline Polygon(const QVector<PT>& polygon) : QVector<Vertex>(polygon.begin(), polygon.end()) {
    }

    inline explicit operator QPolygonF() const {
      QPolygonF ret;
      ret.reserve(size());
      for (auto vertex : *this) {
        ret += vertex;
      }
      return ret;
    }
  };
  #endif