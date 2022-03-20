#ifndef SOCCER_COMMON_SHAREDVALUE_H
#define SOCCER_COMMON_SHAREDVALUE_H

#include <utility>
#include <optional>
#include "soccer-common/Utils/detail/detail.h"

template <class T>
class SharedValue {
  T m_instance;

 public:
  template <class... Args>
  constexpr SharedValue(Args&&... args) : m_instance(std::forward<Args>(args)...) {
  }

  template <class U>
  constexpr void operator=(U&& other) {
    m_instance = std::forward<U>(other);
  }

  constexpr T value() const {
    return m_instance;
  }

  constexpr T get() const {
    return m_instance;
  }

  template <class U = T,
            std::enable_if_t<detail::has_clear_v<U> && detail::has_empty_v<U>, bool> = true>
  bool extract_and_clear(T& value) {
    value = std::move(m_instance);
    m_instance.clear();
    return !value.empty();
  }

  template <class U = T,
            std::enable_if_t<detail::has_clear_v<U> && detail::has_empty_v<U>, bool> = true>
  bool extractAndClear(T& value) {
    return extract_and_clear(value);
  }

  template <class U = T, std::enable_if_t<detail::has_clear_v<U>, bool> = true>
  U get_and_clear() {
    U value = std::move(m_instance);
    m_instance.clear();
    return value;
  }

  template <class U = T, std::enable_if_t<detail::has_clear_v<U>, bool> = true>
  U getAndClear() {
    return get_and_clear();
  }

  template <class U>
  constexpr void set(U&& other) {
    m_instance = std::forward<U>(other);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) {
    return std::forward<FunctionPointer>(f)(m_instance);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) const {
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

template <class T>
class SharedValue<std::optional<T>> {
  std::optional<T> m_instance;

 public:
  template <class... Args>
  constexpr SharedValue(Args&&... args) : m_instance(std::forward<Args>(args)...) {
  }

  template <class U>
  constexpr void operator=(U&& value) {
    m_instance = std::forward<U>(value);
  }

  constexpr explicit operator bool() const {
    return m_instance.operator bool();
  }

  [[nodiscard]] constexpr bool has_value() const {
    return m_instance.has_value();
  }

  template <class U>
  constexpr T value_or(U&& other) const {
    return m_instance.value_or(std::forward<U>(other));
  }

  constexpr void reset() {
    return m_instance.reset();
  }

  constexpr T value() const {
    return m_instance.value();
  }

  constexpr T get() const {
    return m_instance.value();
  }

  T get_and_reset() {
    T ret(std::move(m_instance.value()));
    m_instance.reset();
    return ret;
  }

  T getAndReset() {
    return get_and_reset();
  }

  std::optional<T> get_optional_and_reset() {
    std::optional<T> ret(std::move(m_instance));
    m_instance.reset();
    return ret;
  }

  std::optional<T> getOptionalAndReset() {
    return get_optional_and_reset();
  }

  template <class U>
  bool extract_to(U& other) {
    if (m_instance.has_value()) {
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
  constexpr void set(U&& value) {
    m_instance = std::forward<U>(value);
  }

  template <class... Args>
  void emplace(Args&&... args) {
    m_instance.emplace(std::forward<Args>(args)...);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) {
    return std::forward<FunctionPointer>(f)(m_instance);
  }

  template <class FunctionPointer>
  constexpr decltype(auto) apply(FunctionPointer&& f) const {
    return std::forward<FunctionPointer>(f)(m_instance);
  }

  // observers:
  constexpr T& operator->() {
    return m_instance.operator->();
  }

  constexpr const T& operator->() const {
    return m_instance.operator->();
  }

  constexpr T* operator*() {
    return m_instance.operator*();
  }

  constexpr const T* operator*() const {
    return m_instance.operator*();
  }

  constexpr T& ref() {
    return m_instance.value();
  }
};

template <class T>
using SharedOptional [[maybe_unused]] = SharedValue<std::optional<T>>;

#endif // SOCCER_COMMON_SHAREDVALUE_H
