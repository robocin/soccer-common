#ifndef SOCCER_COMMON_STRINGHELPER_H
#define SOCCER_COMMON_STRINGHELPER_H

#include <QString>

namespace Utils {
  template <class T>
  QString nameOfType() {
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

  template <class T>
  QString nameOfType(T&&) {
    return nameOfType<T>();
  }

  QString quoted(const QString& str);
  QString removeQuotes(const QString& str);
} // namespace Utils

#endif // SOCCER_COMMON_STRINGHELPER_H
