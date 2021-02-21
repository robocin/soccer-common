//
// Created by jose-cruz on 15/02/2021.
//

#ifndef SOCCER_COMMON_OVERLOADED_VISITOR_T_H
#define SOCCER_COMMON_OVERLOADED_VISITOR_T_H

#include <type_traits>
#include <functional>
#include "soccer-common/Utils/StringHelper/StringHelper.h"

namespace detail {
  template <class F>
  static constexpr bool is_function_pointer_v =
      std::is_pointer_v<std::decay_t<F>>&&
          std::is_function_v<std::remove_pointer_t<std::decay_t<F>>>;

  template <class F>
  decltype(auto) make_functor(F&& f) {
    if constexpr (is_function_pointer_v<F>) {
      return std::function(std::forward<F>(f));
    } else {
      return std::forward<F>(f);
    }
  }

  template <class T, class... Ts>
  Extends<QString> overloaded_visitor_rte_message() {
    auto type = Utils::nameOfType<T>();
    auto functors = Utils::nameOfTypes<Ts...>();
    return type + " is not invocable by " + functors + ".";
  }
} // namespace detail

template <class... Ts>
class [[maybe_unused]] overloaded_visitor_t : public Ts... {
  template <class U, class... Us>
  static constexpr bool are_same_v = (std::is_same<U, Us>::value && ...);

  template <class F>
  using functor_result_t =
      typename decltype(std::function(std::declval<F>()))::result_type;

  static_assert(are_same_v<functor_result_t<Ts>...>,
                "result types are not the same.");

  template <class U, class...>
  struct front_type {
    using type = U;
  };

 public:
  explicit overloaded_visitor_t(Ts... functors) : Ts(functors)... {
  }

  using result_type = typename front_type<functor_result_t<Ts>...>::type;
  using Ts::operator()...;

  template <class T>
  std::enable_if_t<!(std::is_invocable_v<Ts, T> || ...), result_type>
  operator()(T&&) const {
    using detail::overloaded_visitor_rte_message;
    throw std::runtime_error(overloaded_visitor_rte_message<T, Ts...>());
  }
};

template <>
class [[maybe_unused]] overloaded_visitor_t<> {
 public:
  overloaded_visitor_t() = default;

  template <class T>
  void operator()(T&&) const {
    using detail::overloaded_visitor_rte_message;
    throw std::runtime_error(overloaded_visitor_rte_message<T>());
  }
};

template <class... Functors>
inline auto make_visitor(Functors&&... functors) {
  return overloaded_visitor_t(
      detail::make_functor(std::forward<Functors>(functors))...);
}

#endif // SOCCER_COMMON_OVERLOADED_VISITOR_T_H