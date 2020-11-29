#ifndef EXTENDSIMPL_H
#define EXTENDSIMPL_H

#include <utility>

template <class T>
class Extends {};

template <class T>
constexpr decltype(auto) extends(T&& object) noexcept {
  if constexpr (std::is_empty_v<Extends<std::decay_t<T>>>) {
    return T(object);
  } else {
    return Extends<std::decay_t<T>>(std::forward<T>(object));
  }
}

#endif // EXTENDSIMPL_H
