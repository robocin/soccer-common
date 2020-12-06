#ifndef EXTENDSIMPL_H
#define EXTENDSIMPL_H

#include <utility>

template <class T>
class Extends {};

template <class T>
Extends(const T&) -> Extends<T>;

template <class T>
constexpr decltype(auto) extends(const T& object) {
  static_assert(!std::is_empty_v<Extends<T>>, "this class has no extension.");
  return Extends<T>(object);
}

#endif // EXTENDSIMPL_H
