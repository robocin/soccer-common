#ifndef SOCCER_COMMON_HUNGARIAN_H
#define SOCCER_COMMON_HUNGARIAN_H

#include <QPair>
#include <QVector>

#include "soccer-common/Geometry/Geometry.h"

#include "tourist/hungarian.h"

class Hungarian {
 public:
  template <class R, class PT>
  inline static QVector<QPair<R, PT>> match(const QVector<R>& robots,
                                            const QVector<PT>& positions) {
    QVector<QPair<R, PT>> result;
    if (!(robots.size() <= positions.size())) {
      return result;
    }
    const int n = static_cast<int>(robots.size());
    const int m = static_cast<int>(positions.size());

    tourist::hungarian<Geometry2D::CoordType<PT>> hungarian(n, m);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        hungarian.a[i][j] = robots[i].distTo(positions[j]);
      }
    }

    hungarian.solve();

    for (int i = 0; i < n; ++i) {
      const auto& position = positions[hungarian.pa[i]];
      result.emplace_back(std::move(robots[i]), position);
    }

    return result;
  }

  template <class R, class PT, class T>
  inline static QVector<QPair<R, QPair<PT, T>>> match(const QVector<R>& robots,
                                                      const QVector<QPair<PT, T>>& positionPairs) {
    QVector<QPair<R, QPair<PT, T>>> result;
    if (!(robots.size() <= positionPairs.size())) {
      return result;
    }
    const int n = static_cast<int>(robots.size());
    const int m = static_cast<int>(positionPairs.size());

    tourist::hungarian<Geometry2D::CoordType<PT>> hungarian(n, m);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        hungarian.a[i][j] = robots[i].distTo(positionPairs[j].first);
      }
    }

    hungarian.solve();

    for (int i = 0; i < n; ++i) {
      const auto& positionPair = positionPairs[hungarian.pa[i]];
      result.emplace_back(std::move(robots[i]), positionPair);
    }

    return result;
  }
};

#endif // SOCCER_COMMON_HUNGARIAN_H
