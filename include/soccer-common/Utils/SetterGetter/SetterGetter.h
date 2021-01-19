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
  constexpr void operator=(U&& other) {
    m_instance = std::forward<U>(other);
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
  constexpr decltype(auto) apply(FunctionPointer&& f) {
    return std::forward<FunctionPointer>(f)(m_instance);
  }

  template <class... Args>
  constexpr void emplace(Args&&... args) {
    m_instance = T(std::forward<Args>(args)...);
  }

  // observers:
  constexpr T* operator->() {
    return std::addressof(m_instance);
  }

  constexpr const T* operator->() const {
    return std::addressof(m_instance);
  }

  constexpr T& operator*() & {
    return m_instance;
  }

  constexpr const T& operator*() const& {
    return m_instance;
  }

  constexpr T& ref() {
    return m_instance;
  }
};

#endif // SETTERGETTER_H
