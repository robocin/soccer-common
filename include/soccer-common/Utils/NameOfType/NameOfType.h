#ifndef SOCCER_COMMON_NAMEOFTYPE_H
#define SOCCER_COMMON_NAMEOFTYPE_H

#include <QString>
#include <variant>

namespace Utils {
  template <class T>
  QString nameOfType() {
    constexpr std::size_t size = sizeof(__PRETTY_FUNCTION__) - 1;
    QString ret;
#if defined(__clang__)
    {
      constexpr std::string_view lhs("QString Utils::nameOfType() [T = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 33; i < size - 1; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
    {
      constexpr std::string_view lhs("QString Utils::nameOfType() [with T = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 38; i < size - 1; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#else
  #error the chosen compiler is not allowed.
#endif
    return ret;
  }

  template <class... Ts>
  QString nameOfTypes() {
    constexpr std::size_t size = sizeof(__PRETTY_FUNCTION__) - 1;
    QString ret;
    ret += "[";
#if defined(__clang__)
    {
      constexpr std::string_view lhs("QString Utils::nameOfTypes() [Ts = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 36; i < size - 2; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
    {
      constexpr std::string_view lhs("QString Utils::nameOfTypes() [with Ts = ");
      constexpr std::string_view rhs(__PRETTY_FUNCTION__,
                                     std::min(sizeof(__PRETTY_FUNCTION__), lhs.size()));
      static_assert(lhs == rhs, "function name is not as expected.");
    }
    for (std::size_t i = 41; i < size - 2; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#else
  #error the chosen compiler is not allowed.
#endif
    ret += "]";
    return ret;
  }

  template <class T>
  QString nameOfType(T&&) {
    return nameOfType<T>();
  }

  template <class... Ts>
  QString nameOfTypes(Ts&&...) {
    return nameOfTypes<Ts...>();
  }

  template <class T>
  QString nameOfCurrentType(T&& variant) {
    return std::visit(
        [](auto&& value) {
          using U = std::decay_t<decltype(value)>;
          return Utils::nameOfType<U>();
        },
        std::forward<T>(variant));
  }

  QString quoted(const QString& str);
  QString removeQuotes(const QString& str);

  QString removeScope(const QString& str);
} // namespace Utils

#endif // SOCCER_COMMON_NAMEOFTYPE_H
