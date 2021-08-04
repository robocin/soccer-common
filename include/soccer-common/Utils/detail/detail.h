//
// Created by jose-cruz on 23/07/2021.
//

#ifndef SOCCER_COMMON_DETAIL_H
#define SOCCER_COMMON_DETAIL_H

#include <variant>
#include <utility>
#include <functional>

namespace detail {
  template <class F>
  inline constexpr bool is_function_pointer_v = std::is_pointer_v<std::decay_t<F>>&&
      std::is_function_v<std::remove_pointer_t<std::decay_t<F>>>;

  template <class F>
  decltype(auto) make_functor(F&& f) {
    if constexpr (is_function_pointer_v<F>) {
      return std::function(std::forward<F>(f));
    } else {
      return std::forward<F>(f);
    }
  }

  template <class U, class... Us>
  inline constexpr bool is_any_of_v = std::disjunction_v<std::is_same<U, Us>...>;

  template <class U, class = void>
  struct is_iterable : std::false_type {};

  template <class U>
  struct is_iterable<
      U,
      std::void_t<decltype(std::begin(std::declval<U>())), decltype(std::end(std::declval<U>()))>>
      : std::true_type {};

  template <class U>
  inline constexpr bool is_iterable_v = is_iterable<U>::value;

  template <class U, class V = void>
  struct has_find : std::false_type {};

  template <class U>
  struct has_find<
      U,
      std::void_t<typename U::key_type,
                  decltype(std::declval<U&>().find(std::declval<const typename U::key_type&>()))>>
      : std::true_type {};

  template <class U>
  inline constexpr bool has_find_v = has_find<U>::value;

  template <class U, class V = void>
  struct has_contains : std::false_type {};

  template <class U>
  struct has_contains<U,
                      std::void_t<typename U::key_type,
                                  decltype(std::declval<U&>().contains(
                                      std::declval<const typename U::key_type&>()))>>
      : std::true_type {};

  template <class U>
  inline constexpr bool has_contains_v = has_contains<U>::value;

  template <class U, class V = void>
  struct has_clear : std::false_type {};

  template <class U>
  struct has_clear<U, std::void_t<decltype(std::declval<U>().clear())>> : std::true_type {};

  template <class U>
  inline constexpr bool has_clear_v = has_clear<U>::value;

  template <class U>
  inline constexpr bool dependent_false_v = false;

  template <typename T>
  struct is_variant : std::false_type {};

  template <typename... Args>
  struct is_variant<std::variant<Args...>> : std::true_type {};

  template <typename T>
  inline constexpr bool is_variant_v = is_variant<T>::value;

  template <class T>
  struct is_tuple : std::false_type {};

  template <class... Ts>
  struct is_tuple<std::tuple<Ts...>> : std::true_type {};

  template <class T>
  constexpr bool is_tuple_v = is_tuple<T>::value;

  template <class T>
  struct is_optional : std::false_type {};

  template <class T>
  struct is_optional<std::optional<T>> : std::true_type {};

  template <class T>
  constexpr bool is_optional_v = is_optional<T>::value;

  template <class T>
  constexpr bool is_c_str_v = std::is_same_v<const char*, std::decay_t<T>>;

  template <class, class... Ts>
  struct has_common_type : std::false_type {};

  template <class... Ts>
  struct has_common_type<std::void_t<std::common_type_t<Ts...>>, Ts...> : std::true_type {};

  template <class... Ts>
  inline constexpr bool has_common_type_v = has_common_type<Ts...>::value;

  template <class S, class C, class = void>
  struct is_streamable : ::std::false_type {};

  template <class S, class C>
  struct is_streamable<S, C, std::void_t<decltype(std::declval<S&>() << std::declval<C const&>())>>
      : ::std::true_type {};

  template <class S, class C>
  inline constexpr bool is_streamable_v = is_streamable<S, C>::value;
} // namespace detail

#endif // SOCCER_COMMON_DETAIL_H
