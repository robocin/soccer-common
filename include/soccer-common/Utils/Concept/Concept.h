//
// Created by jose-cruz on 08/05/2022.
//

#ifndef SOCCER_COMMON_CONCEPT_H
#define SOCCER_COMMON_CONCEPT_H

#include <variant>
#include <utility>

namespace Concept {
  namespace Detail {
    template <class T>
    struct is_variant : std::false_type {};

    template <class... Args>
    struct is_variant<std::variant<Args...>> : std::true_type {};

    template <class T>
    inline constexpr bool is_variant_v = is_variant<T>::value;

    template <class T>
    struct is_tuple : std::false_type {};

    template <class... Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

    template <class T>
    inline constexpr bool is_tuple_v = is_tuple<T>::value;

    template <class T>
    struct is_pair : std::false_type {};

    template <class U, class V>
    struct is_pair<std::pair<U, V>> : std::true_type {};

    template <class T>
    inline constexpr bool is_pair_v = is_pair<T>::value;
  } // namespace Detail

  template <class V>
  concept Variant = Detail::is_variant_v<V>;

  template <class T>
  concept Tuple = Detail::is_tuple_v<T>;

  template <class P>
  concept Pair = Detail::is_pair_v<P>;

  template <class F, class... Args>
  concept MatchingFunctor = requires(F functor, Args&&... args) {
    functor.operator()(std::forward<Args>(args)...);
  };

  template <class V, class... Vs>
  concept MatchingVisitor = requires(V visitor, Vs&&... variants) {
    std::visit(visitor, std::forward<Vs>(variants)...);
  };

  template <class T>
  concept Cleanable = requires(T type) {
    type.clear();
  };

  template <class T, class... Ts>
  concept OneOf = (std::same_as<T, Ts> || ...);
} // namespace Concept

#endif // SOCCER_COMMON_CONCEPT_H
