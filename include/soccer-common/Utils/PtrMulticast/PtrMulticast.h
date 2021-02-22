#ifndef SOCCER_COMMON_PTRMULTICAST_H
#define SOCCER_COMMON_PTRMULTICAST_H

#include <type_traits>

template <class T>
class PtrCastOperator {
  T* m_ptr;

  template <class U>
  static constexpr T* makeT([[maybe_unused]] U* ptr) {
    if constexpr (std::is_same_v<T, U> || std::is_base_of_v<T, U>) {
      return static_cast<T*>(ptr);
    } else {
      return nullptr;
    }
  }

 public:
  constexpr PtrCastOperator(std::nullptr_t null = nullptr) : m_ptr(null) {
  }
  template <class U>
  constexpr PtrCastOperator(U* ptr) : m_ptr(makeT(ptr)) {
  }
  constexpr operator T*() {
    return m_ptr;
  }
  constexpr operator const T*() const {
    return m_ptr;
  }
};

template <class... Args>
class PtrMulticast : public PtrCastOperator<Args>... {
  template <class U>
  static constexpr bool is_any_of_v = std::disjunction_v<std::is_same<U, Args>...>;

 public:
  constexpr PtrMulticast(std::nullptr_t ptr = nullptr) : PtrCastOperator<Args>(ptr)... {
  }
  template <class T>
  constexpr PtrMulticast(T* ptr) : PtrCastOperator<Args>(ptr)... {
  }

  template <class U>
  constexpr operator U*() {
    if constexpr (is_any_of_v<U>) {
      return operator U*();
    } else {
      return nullptr;
    }
  }

  template <class U>
  constexpr operator const U*() const {
    if constexpr (is_any_of_v<U>) {
      return operator const U*();
    } else {
      return nullptr;
    }
  }
};

#endif // SOCCER_COMMON_PTRMULTICAST_H
