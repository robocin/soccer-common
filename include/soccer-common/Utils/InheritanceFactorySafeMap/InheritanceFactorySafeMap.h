#ifndef INHERITANCEFACTORYSAFEMAP_H
#define INHERITANCEFACTORYSAFEMAP_H

#include <QMap>
#include <mutex>
#include <QMutex>
#include <functional>
#include "soccer-common/Utils/StringHelper/StringHelper.h"

template <class T, class... Args>
class InheritanceFactorySafeMap {
  using Key = QString;
  using Value = QPair<std::function<T*(Args&&...)>, QString>;

  mutable QMutex mutex;
  QMap<Key, Value> m_map;

  template <class U>
  static T* makeFactory(Args&&... args) {
    return new U(std::forward<Args>(args)...);
  }

 public:
  template <class U>
  void insert(const QString& description) {
    static_assert(std::is_base_of_v<T, U>);
    std::lock_guard locker(mutex);
    m_map.insert(Utils::nameOfType<U>(), QPair(makeFactory<U>, description));
  }

  int size() const {
    std::lock_guard locker(mutex);
    return m_map.size();
  }

  QStringList keys() const {
    std::lock_guard locker(mutex);
    return m_map.keys();
  }

  QMap<Key, Value> map() const {
    std::lock_guard locker(mutex);
    return m_map;
  }

  Value operator[](const Key& key) const {
    std::lock_guard locker(mutex);
    return m_map[key];
  }
};

#endif // INHERITANCEFACTORYSAFEMAP_H
