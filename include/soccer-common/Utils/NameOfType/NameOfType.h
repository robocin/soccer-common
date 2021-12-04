#ifndef SOCCER_COMMON_NAMEOFTYPE_H
#define SOCCER_COMMON_NAMEOFTYPE_H

#include <QString>
#include <variant>
#include "soccer-common/Extends/QString/ExtendsQString.h"

namespace Utils {
  template <class T>
  Extends<QString> nameOfType() {
    constexpr std::size_t size = sizeof(__PRETTY_FUNCTION__) - 1;
    QString ret;
#if defined(__clang__)
    {
      constexpr std::string_view lhs("Extends<QString> Utils::nameOfType() [T = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 42; i < size - 1; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
    {
      constexpr std::string_view lhs("Extends<QString> Utils::nameOfType() [with T = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 47; i < size - 1; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#else
  #error the chosen compiler is not allowed.
#endif
    return ret;
  }

  template <class... Ts>
  Extends<QString> nameOfTypes() {
    constexpr std::size_t size = sizeof(__PRETTY_FUNCTION__) - 1;
    QString ret;
    ret += "[";
#if defined(__clang__)
    {
      constexpr std::string_view lhs("Extends<QString> Utils::nameOfTypes() [Ts = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 45; i < size - 2; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
    {
      constexpr std::string_view lhs("Extends<QString> Utils::nameOfTypes() [with Ts = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 50; i < size - 2; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#else
  #error the chosen compiler is not allowed.
#endif
    ret += "]";
    return ret;
  }

  template <class T>
  Extends<QString> nameOfType(T&&) {
    return nameOfType<T>();
  }

  template <class... Ts>
  Extends<QString> nameOfTypes(Ts&&...) {
    return nameOfTypes<Ts...>();
  }

  template <class T>
  Extends<QString> nameOfCurrentType(T&& variant) {
    return std::visit(
        [](auto&& value) {
          using U = std::decay_t<decltype(value)>;
          return Utils::nameOfType<U>();
        },
        std::forward<T>(variant));
  }

  Extends<QString> quoted(const QString& str);
  Extends<QString> removeQuotes(const QString& str);

  Extends<QString> removeScope(const QString& str);
} // namespace Utils

#endif // SOCCER_COMMON_NAMEOFTYPE_H
