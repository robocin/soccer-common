#ifndef SOCCER_COMMON_EXTENDSIMPL_H
#define SOCCER_COMMON_EXTENDSIMPL_H

#include <utility>

template <class T>
class Extends {
  template <class U>
  static constexpr bool dependent_false_v = false;

  static_assert(dependent_false_v<T>, "this class has no extension.");
};

template <class T>
Extends(const T&) -> Extends<T>;

template <class T>
constexpr decltype(auto) extends(const T& object) {
  return Extends<T>(object);
}

#endif // SOCCER_COMMON_EXTENDSIMPL_H