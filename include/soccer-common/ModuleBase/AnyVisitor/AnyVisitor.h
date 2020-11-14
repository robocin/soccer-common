#ifndef ANYVISITOR_H
#define ANYVISITOR_H

#include <typeindex>
#include "soccer-common/ModuleBase/ModulePrivate/ModulePrivate.h"

class ModulePrivate::AnyVisitor {
  using Key = const std::type_index;
  using Value = std::function<void(const std::any&)>;
  std::map<Key, Value> visitor;

 public:
  template <class T, class F>
  void insert(F&& f) {
    static_assert(not std::is_same_v<T, std::any>,
                  "std::any cannot be registered.");
    if (visitor.find(typeid(T)) != visitor.end()) {
      throw std::runtime_error("inserting the same type more than once.");
    }
    visitor[typeid(T)] = [g = std::forward<F>(f)](const std::any& a) {
      if constexpr (std::is_void_v<T>) {
        g();
      } else {
        g(std::any_cast<const T&>(a));
      }
    };
  }

  inline void operator()(const std::any& a) const {
    if (auto it = visitor.find(a.type()); it != visitor.end()) {
      it->second(a);
    } else {
      throw std::runtime_error("unregistered type.");
    }
  }
};

#endif // ANYVISITOR_H
