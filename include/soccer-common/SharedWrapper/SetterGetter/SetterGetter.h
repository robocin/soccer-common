#ifndef SETTERGETTER_H
#define SETTERGETTER_H

#include <utility>

template <class T>
class SetterGetter {
  T m_instance;

 public:
  template <class... Args>
  SetterGetter(Args&&... args) : m_instance(std::forward<Args>(args)...) {
  }

  template <class U>
  void set(U&& other) {
    m_instance = other;
  }

  template <class... Args>
  void emplace(Args&&... args) {
    m_instance = T(std::forward<Args>(args)...);
  }

  T get() const {
    return m_instance;
  }
};

#endif // SETTERGETTER_H
