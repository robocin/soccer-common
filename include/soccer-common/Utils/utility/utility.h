//
// Created by jose-cruz on 13/08/2021.
//

#ifndef SOCCER_COMMON_UTILITY_H
#define SOCCER_COMMON_UTILITY_H

#include <utility>
#include <array>

namespace Utils {
  namespace detail {
    template <class T, std::size_t N, std::size_t... Is, class... Args>
    std::array<T, N> make_array(std::index_sequence<Is...>, Args&&... args) {
      return std::array<T, N>({(Is, T(std::forward<Args>(args)...))...});
    }
  } // namespace detail

  template <class T, std::size_t N, class... Args>
  std::array<T, N> make_array(Args&&... args) {
    return detail::make_array<T, N>(std::make_index_sequence<N>{}, std::forward<Args>(args)...);
  }
} // namespace Utils

#endif // SOCCER_COMMON_UTILITY_H
