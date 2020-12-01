#ifndef EXTENDSIMPL_H
#define EXTENDSIMPL_H

#include <utility>

namespace detail {
  template <class T, class... Args>
  using enable_if_any_t =
      std::enable_if_t<(std::is_same_v<std::decay_t<T>, Args> || ...)>;

  template <class T>
  constexpr bool dependent_false_v = false;
} // namespace detail

template <class T, class U = void>
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
