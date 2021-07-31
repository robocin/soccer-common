#ifndef SOCCER_COMMON_SHAREDOPTIONAL_H
#define SOCCER_COMMON_SHAREDOPTIONAL_H

#include <optional>

template <class T>
class SharedOptional : public std::optional<T> {
 public:
  template <class... Args>
  constexpr SharedOptional(Args&&... args) : std::optional<T>(std::forward<Args>(args)...) {
  }

  template <class U>
  constexpr void operator=(U&& value) {
    std::optional<T>::operator=(std::forward<U>(value));
  }

  using std::optional<T>::operator bool;
  using std::optional<T>::has_value;
  using std::optional<T>::value_or;
  using std::optional<T>::reset;

  constexpr T value() const {
    return std::optional<T>::value();
  }

  constexpr T get() const {
    return std::optional<T>::value();
  }

  T getAndReset() {
    T ret(std::move(std::optional<T>::value()));
    std::optional<T>::reset();
    return ret;
  }

  template <class U>
  bool extract_to(U& other) {
    if (has_value()) {
      other = static_cast<U>(getAndReset());
      return true;
    }
    return false;
  }

  template <class U>
  bool extractTo(U& other) {
    return extract_to(other);
  }

  template <class U>
  bool extract_to(std::optional<U>& other) {
    if (has_value()) {
      other.template emplace(static_cast<U>(getAndReset()));
      return true;
    }
    return false;
  }

  template <class U>
  bool extractTo(std::optional<U>& other) {
    return extract_to(other);
  }

  template <class U>
  constexpr decltype(auto) getOrElse(U&& value) const {
    return std::optional<T>::value_or(std::forward<U>(value));
  }

  template <class U>
  constexpr void set(U&& value) {
    std::optional<T>::operator=(std::forward<U>(value));
  }

  template <class... Args>
  void emplace(Args&&... args) {
    std::optional<T>::emplace(std::forward<Args>(args)...);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) {
    return std::forward<FunctionPointer>(f)(*this);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) const {
    return std::forward<FunctionPointer>(f)(*this);
  }

  // observers:
  using std::optional<T>::operator->;
  using std::optional<T>::operator*;

  constexpr std::optional<T>& ref() {
    return static_cast<std::optional<T>&>(*this);
  }

 private:
  using std::optional<T>::operator=;
  using std::optional<T>::emplace;
  using std::optional<T>::swap;
};

#endif // SOCCER_COMMON_SHAREDOPTIONAL_H
