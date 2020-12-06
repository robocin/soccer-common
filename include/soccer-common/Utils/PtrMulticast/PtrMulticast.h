#ifndef PTRMULTICAST_H
#define PTRMULTICAST_H

#include <type_traits>

template <class T>
class PtrCastOperator {
  T* m_ptr;

  template <class U>
  static constexpr T* makeT([[maybe_unused]] U* ptr) {
    if constexpr (std::is_base_of_v<T, U>) {
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
 public:
  constexpr PtrMulticast(std::nullptr_t null = nullptr) :
      PtrCastOperator<Args>(null)... {
  }
  template <class T>
  constexpr PtrMulticast(T* ptr) : PtrCastOperator<Args>(ptr)... {
  }
};

#endif // PTRMULTICAST_H
