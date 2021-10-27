#ifndef SOCCER_COMMON_INHERITANCEFACTORY_H
#define SOCCER_COMMON_INHERITANCEFACTORY_H

#include <QMap>
#include <mutex>
#include <functional>
#include <utility>
#include "soccer-common/Utils/NameOfType/NameOfType.h"

template <class T, class... Args>
class InheritanceFactory {
  using Key = QString;
  class Value : public std::function<T*(Args...)> {
    QString m_description;

   public:
    Value() = default;

    template <class F>
    Value(F&& f, QString description) :
        std::function<T*(Args...)>(std::forward<F>(f)),
        m_description(std::move(description)) {
    }

    [[nodiscard]] QString description() const {
      return m_description;
    }
  };

  QMap<Key, Value> m_map;
  mutable std::mutex m_mutex;

  template <class U>
  static T* makeFactory(Args... args) {
    return new U(args...);
  }

 public:
  using type = QMap<Key, Value>;

  template <class U>
  std::enable_if_t<std::is_base_of_v<T, U>> insert(QString description = "") {
    std::lock_guard locker(m_mutex);
    m_map.insert(Utils::nameOfType<U>(), Value(makeFactory<U>, std::move(description)));
  }

  int size() const {
    std::lock_guard locker(m_mutex);
    return m_map.size();
  }

  int empty() const {
    std::lock_guard locker(m_mutex);
    return m_map.empty();
  }

  QStringList keys() const {
    std::lock_guard locker(m_mutex);
    return m_map.keys();
  }

  QMap<Key, Value> map() const {
    std::lock_guard locker(m_mutex);
    return m_map;
  }

  explicit operator QMap<Key, Value>() const {
    std::lock_guard locker(m_mutex);
    return m_map;
  }

  Value operator[](const Key& key) const {
    std::lock_guard locker(m_mutex);
    return m_map[key];
  }
};

#endif // SOCCER_COMMON_INHERITANCEFACTORY_H
