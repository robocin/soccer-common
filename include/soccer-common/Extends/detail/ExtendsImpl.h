#ifndef EXTENDSIMPL_H
#define EXTENDSIMPL_H

#include <utility>

namespace detail {
  template <class T>
  constexpr bool dependent_false_v = false;
} // namespace detail

template <class T>
class Extends {};

template <class T>
Extends(const T&) -> Extends<T>;

template <class T>
constexpr decltype(auto) extends(const T& object) {
  if constexpr (std::is_empty_v<Extends<T>>) {
    static_assert(detail::dependent_false_v<T>, "this class has no extension.");
  }
  return Extends<T>(object);
}

#endif // EXTENDSIMPL_H
