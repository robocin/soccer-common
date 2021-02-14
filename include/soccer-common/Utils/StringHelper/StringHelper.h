#ifndef SOCCER_COMMON_STRINGHELPER_H
#define SOCCER_COMMON_STRINGHELPER_H

#include <QString>
#include "soccer-common/Extends/QString/ExtendsQString.h"

namespace Utils {
  template <class T>
  Extends<QString> nameOfType() {
    constexpr std::size_t size = sizeof(__PRETTY_FUNCTION__) - 1;
    QString ret;
#if defined(__clang__)
    for (std::size_t i = 33; i < size - 1; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
    for (std::size_t i = 38; i < size - 1; ++i) {
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
    for (std::size_t i = 36; i < size - 2; ++i) {
      ret += __PRETTY_FUNCTION__[i];
    }
#elif defined(__GNUC__)
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
  Extends<QString> nameOfType(T&&) {
    return nameOfType<T>();
  }

  template <class... Ts>
  Extends<QString> nameOfTypes(Ts&&...) {
    return nameOfTypes<Ts...>();
  }

  Extends<QString> quoted(const QString& str);
  Extends<QString> removeQuotes(const QString& str);
} // namespace Utils

#endif // SOCCER_COMMON_STRINGHELPER_H
