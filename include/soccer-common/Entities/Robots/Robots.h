//
// Created by jose-cruz on 12/07/2021.
//

#ifndef SOCCER_COMMON_ROBOTS_H
#define SOCCER_COMMON_ROBOTS_H

#include <QList>
#include <optional>
#include "soccer-common/Geometry/Geometry.h"

namespace Common {
  template <class R>
  class Robots : public QList<R> {
    using PT = decltype(std::declval<R>().position());
    using id_type = decltype(std::declval<R>().id());
    using const_iterator = typename QList<R>::const_iterator;
    using iterator = typename QList<R>::iterator;

   public:
    explicit Robots(const QList<R>& other) : QList<R>(other) {
    }
    explicit Robots(QList<R>&& other) : QList<R>(std::forward<QList<R>>(other)) {
    }
    template <class InputIterator>
    Robots(InputIterator first, InputIterator last) : QList<R>(first, last) {
    }
    Robots(std::initializer_list<R> args) : QList<R>(args) {
    }
    Robots() : QList<R>() {
    }

    iterator find(const R& robot) {
      return std::find(QList<R>::begin(), QList<R>::end(), robot);
    }

    const_iterator find(const R& robot) const {
      return std::find(QList<R>::cbegin(), QList<R>::cend(), robot);
    }

    template <class Functor>
    iterator findIf(Functor&& f) {
      return std::find_if(QList<R>::begin(), QList<R>::end(), std::forward<Functor>(f));
    }

    template <class Functor>
    const_iterator findIf(Functor&& f) const {
      return std::find_if(QList<R>::cbegin(), QList<R>::cend(), std::forward<Functor>(f));
    }

    template <class Functor>
    QList<iterator> findAll(Functor&& f) {
      QList<iterator> ret;
      auto first = QList<R>::begin();
      auto last = QList<R>::end();
      while (first != last) {
        if (auto it = std::find_if(first, last, std::forward<Functor>(f)); first = it, it != last) {
          ret.template emplace_back(it);
          ++first;
        }
      }
      return ret;
    }

    template <class Functor>
    QList<const_iterator> findAll(Functor&& f) const {
      QList<const_iterator> ret;
      auto first = QList<R>::cbegin();
      auto last = QList<R>::cend();
      while (first != last) {
        if (auto it = std::find_if(first, last, std::forward<Functor>(f)); first = it, it != last) {
          ret.template emplace_back(it);
          ++first;
        }
      }
      return ret;
    }

    iterator findById(id_type id) {
      return findIf([id](const R& robot) {
        return id == robot.id();
      });
    }

    const_iterator findById(id_type id) const {
      return findIf([id](const R& robot) {
        return id == robot.id();
      });
    }

    void removeById(id_type id) {
      QList<R>::removeIf([id](const R& robot) {
        return id == robot.id();
      });
    }

    Robots<R> removed(const R& robot) const {
      Robots<R> robots(*this);
      robots.removeAll(robot);
      return robots;
    }

    Robots<R> removedById(id_type id) const {
      Robots<R> robots(*this);
      robots.removeById(id);
      return robots;
    }

    iterator closestTo(const PT& position) {
      std::optional<iterator> closest;
      for (auto it = QList<R>::begin(); it != QList<R>::end(); ++it) {
        if (closest) {
          if (Geometry2D::distanceSquared<PT>(position, it->position()) <
              Geometry2D::distanceSquared<PT>(position, closest.value()->position())) {
            closest.template emplace(it);
          }
        } else {
          closest.template emplace(it);
        }
      }
      return closest.template value_or(QList<R>::end());
    }

    const_iterator closestTo(const PT& position) const {
      std::optional<const_iterator> closest;
      for (auto it = QList<R>::cbegin(); it != QList<R>::cend(); ++it) {
        if (closest) {
          if (Geometry2D::distanceSquared<PT>(position, it->position()) <
              Geometry2D::distanceSquared<PT>(position, closest.value()->position())) {
            closest.template emplace(it);
          }
        } else {
          closest.template emplace(it);
        }
      }
      return closest.template value_or(QList<R>::cend());
    }

    QList<id_type> ids() const {
      QList<id_type> ids;
      ids.reserve(QList<R>::size());
      for (const R& robot : static_cast<const QList<R>&>(*this)) {
        ids.template emplace_back(robot.id());
      }
      return ids;
    }

    iterator operator[](id_type id) {
      return findById(id);
    }

    const_iterator operator[](id_type id) const {
      return findById(id);
    }

   private:
    using QList<R>::operator[];
  };
} // namespace Common

#endif // SOCCER_COMMON_ROBOTS_H
