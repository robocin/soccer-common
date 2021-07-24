//
// Created by jose-cruz on 15/02/2021.
//

#ifndef SOCCER_COMMON_OVERLOADED_VISITOR_T_H
#define SOCCER_COMMON_OVERLOADED_VISITOR_T_H

#include <type_traits>
#include <functional>
#include "soccer-common/Utils/detail/detail.h"
#include "soccer-common/Utils/StringHelper/StringHelper.h"

template <class... Ts>
class [[maybe_unused]] overloaded_visitor_t : public Ts... {
 protected:
  template <class U, class... Us>
  static constexpr bool are_same_v = (std::is_same<U, Us>::value && ...);

  template <class F>
  using functor_result_t = typename decltype(std::function(std::declval<F>()))::result_type;

  static_assert(are_same_v<functor_result_t<Ts>...>, "result types are not the same.");

  template <class U, class...>
  struct front_type {
    using type = U;
  };

 public:
  overloaded_visitor_t() = default;
  explicit overloaded_visitor_t(Ts... functors) : Ts(functors)... {
  }

  using result_type = typename front_type<functor_result_t<Ts>...>::type;
  using Ts::operator()...;

  template <class T>
  std::enable_if_t<!(std::is_invocable_v<Ts, T> || ...), result_type> operator()(T&&) const {
    auto type = Utils::nameOfType<T>();
    auto functors = Utils::nameOfTypes<Ts...>();
    throw std::runtime_error(type + " is not invocable by " + functors + ".");
  }
};

template <>
class [[maybe_unused]] overloaded_visitor_t<> {
 public:
  overloaded_visitor_t() = default;

  using result_type = void;

  template <class T>
  void operator()(T&&) const {
    auto type = Utils::nameOfType<T>();
    auto functors = Utils::nameOfTypes();
    throw std::runtime_error(type + " is not invocable by " + functors + ".");
  }
};

template <class... Functors>
inline auto make_visitor(Functors&&... functors) {
  return overloaded_visitor_t(detail::make_functor(std::forward<Functors>(functors))...);
}

#endif // SOCCER_COMMON_OVERLOADED_VISITOR_T_H
