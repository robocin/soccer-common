#ifndef UTILS_H
#define UTILS_H

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
    static_assert(std::false_type::value,
                  "the chosen compiler is not allowed.");
#endif
    return ret;
  }

  template <class T>
  QString nameOfTypeFromValue(const T&) {
    return nameOfType<T>();
  }
} // namespace Utils

#endif // UTILS_H
