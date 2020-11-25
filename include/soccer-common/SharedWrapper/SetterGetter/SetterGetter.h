#ifndef SETTERGETTER_H
#define SETTERGETTER_H

#include <utility>

template <class T>
class SetterGetter {
  T m_instance;

 public:
  template <class... Args>
  constexpr SetterGetter(Args&&... args) :
      m_instance(std::forward<Args>(args)...) {
  }

  template <class U>
  constexpr SetterGetter& operator=(U&& other) {
    m_instance = std::forward<U>(other);
    return *this;
  }

  constexpr operator T() const {
    return m_instance;
  }

  constexpr T get() const {
    return m_instance;
  }

  template <class U>
  constexpr void set(U&& other) {
    m_instance = std::forward<U>(other);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(const FunctionPointer& f) {
    return f(m_instance);
  }

  template <class... Args>
  constexpr void emplace(Args&&... args) {
    m_instance = T(std::forward<Args>(args)...);
  }
};

#endif // SETTERGETTER_H
