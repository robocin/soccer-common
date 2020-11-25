#ifndef SHAREDOPTIONAL_H
#define SHAREDOPTIONAL_H

#include <optional>

template <class T>
class SharedOptional : public std::optional<T> {
 public:
  template <class... Args>
  constexpr SharedOptional(Args&&... args) :
      std::optional<T>(std::forward<Args>(args)...) {
  }

  template <class U>
  constexpr void operator=(U&& value) {
    std::optional<T>::operator=(std::forward(value));
  }

  using std::optional<T>::operator bool;
  using std::optional<T>::has_value;
  using std::optional<T>::value_or;
  using std::optional<T>::reset;
  using std::optional<T>::emplace;

  constexpr operator T() const {
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
  constexpr decltype(auto) getOrElse(U&& value) {
    return std::optional<T>::value_or(std::forward(value));
  }

  template <class U>
  void set(U&& value) {
    std::optional<T>::operator=(std::forward(value));
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(const FunctionPointer& f) {
    return f(std::optional<T>::value());
  }

 private:
  using std::optional<T>::operator=;
  using std::optional<T>::operator->;
  using std::optional<T>::operator*;
  using std::optional<T>::value;
  using std::optional<T>::swap;
};

#endif // SHAREDOPTIONAL_H
