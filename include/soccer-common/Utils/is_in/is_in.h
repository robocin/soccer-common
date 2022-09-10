//
// Created by jose-cruz on 23/07/2021.
//

#ifndef SOCCER_COMMON_IS_IN_H
#define SOCCER_COMMON_IS_IN_H

#include "soccer-common/Utils/Detail/Detail.h"

#ifdef SOCCER_COMMON_IS_IN_H_UNDEF_IS_IN
namespace Utils {
#endif
  // signatures --------------------------------------------------------------------------------- //

  template <class T, class... Args>
  constexpr std::enable_if_t<(sizeof...(Args) > 1), bool> is_in(T&&, Args&&...);

  template <class T, class U>
  constexpr std::enable_if_t<std::is_same_v<std::decay_t<T>, std::common_type_t<T, U>>, bool>
  is_in(T&&, U&&);

  template <class T, class Tuple>
  constexpr std::enable_if_t<Detail::is_tuple_v<std::decay_t<Tuple>>, bool> is_in(T&&, Tuple&&);

  template <class T, class Optional>
  constexpr std::enable_if_t<Detail::is_optional_v<std::decay_t<Optional>>, bool> is_in(T&&,
                                                                                        Optional&&);

  template <class T, class Variant>
  constexpr std::enable_if_t<Detail::is_variant_v<std::decay_t<Variant>>, bool> is_in(T&&,
                                                                                      Variant&&);

  template <class T, class U>
  constexpr bool is_in(T&&, std::initializer_list<U>);

  template <class T, class U>
  constexpr std::enable_if_t<Detail::is_c_str_v<std::decay_t<U>>, bool> is_in(T&&, U&&);

  template <class T, class Container>
  constexpr std::enable_if_t<Detail::is_iterable_v<std::decay_t<Container>>, bool>
  is_in(T&&, Container&&);

  // -------------------------------------------------------------------------------------------- //

  template <class T, class... Args>
  constexpr std::enable_if_t<(sizeof...(Args) > 1), bool> is_in(T&& lhs, Args&&... args) {
    return (is_in(std::forward<T>(lhs), std::forward<Args>(args)) || ...);
  }

  template <class T, class U>
  constexpr std::enable_if_t<std::is_same_v<std::decay_t<T>, std::common_type_t<T, U>>, bool>
  is_in(T&& lhs, U&& rhs) {
    return std::forward<T>(lhs) == std::forward<U>(rhs);
  }

  template <class T, class Tuple>
  constexpr std::enable_if_t<Detail::is_tuple_v<std::decay_t<Tuple>>, bool> is_in(T&& lhs,
                                                                                  Tuple&& tuple) {
    return std::apply(
        [&](auto&&... args) -> bool {
          return (is_in(std::forward<T>(lhs), std::forward<decltype(args)>(args)) || ...);
        },
        std::forward<Tuple>(tuple));
  }

  template <class T, class Optional>
  constexpr std::enable_if_t<Detail::is_optional_v<std::decay_t<Optional>>, bool>
  is_in(T&& lhs, Optional&& optional) {
    return std::forward<T>(lhs) == std::forward<Optional>(optional);
  }

  template <class T, class Variant>
  constexpr std::enable_if_t<Detail::is_variant_v<std::decay_t<Variant>>, bool>
  is_in(T&& lhs, Variant&& variant) {
    return std::visit(
        [&](auto&& rhs) {
          return is_in(std::forward<T>(lhs), std::forward<decltype(rhs)>(rhs));
        },
        std::forward<Variant>(variant));
  }

  template <class T, class U>
  constexpr bool is_in(T&& lhs, std::initializer_list<U> list) {
    for (auto&& rhs : list) {
      if (std::forward<T>(lhs) == std::forward<decltype(rhs)>(rhs)) {
        return true;
      }
    }
    return false;
  }

  template <class T, class U>
  constexpr std::enable_if_t<Detail::is_c_str_v<std::decay_t<U>>, bool> is_in(T&& lhs, U&& str) {
    for (auto ptr = std::forward<U>(str); static_cast<bool>(*ptr); ++ptr) {
      if (std::forward<T>(lhs) == *ptr) {
        return true;
      }
    }
    return false;
  }

  template <class T, class U>
  constexpr std::enable_if_t<Detail::is_iterable_v<std::decay_t<U>>, bool> is_in(T&& lhs,
                                                                                 U&& container) {
    if constexpr (Detail::has_contains_v<std::decay_t<U>>) {
      return std::forward<U>(container).contains(std::forward<T>(lhs));
    } else if constexpr (Detail::has_find_v<std::decay_t<U>>) {
      return std::forward<U>(container).find(std::forward<T>(lhs)) !=
             std::forward<U>(container).end();
    } else {
      for (auto&& rhs : std::forward<U>(container)) {
        if (std::forward<T>(lhs) == std::forward<decltype(rhs)>(rhs)) {
          return true;
        }
      }
      return false;
    }
  }
#ifdef SOCCER_COMMON_IS_IN_H_UNDEF_IS_IN
} // namespace Utils
#endif

#endif // SOCCER_COMMON_IS_IN_H
