#ifndef SHAREDWRAPPER_H
#define SHAREDWRAPPER_H

#include <mutex>
#include "SharedOptional/SharedOptional.h"
#include "SetterGetter/SetterGetter.h"

template <class T, class Mutex, class Locker = std::lock_guard<Mutex>>
class SharedWrapper {
  class Proxy;
  struct shared_wrapper_tag {};
  static constexpr shared_wrapper_tag tag{};

 public:
  template <class... Args>
  SharedWrapper(Args&&... args) : instance(std::forward<Args>(args)...) {
  }

  ~SharedWrapper() {
  }

  // disable_copy:
  SharedWrapper(const SharedWrapper&) = delete;
  SharedWrapper& operator=(const SharedWrapper&) = delete;

  // disable_move:
  SharedWrapper(SharedWrapper&&) = delete;
  SharedWrapper& operator=(SharedWrapper&&) = delete;

  T get() const {
    Locker locker(mutex);
    return instance;
  }

  template <class U>
  void set(U&& value) {
    Locker locker(mutex);
    instance = value;
  }

  template <class... Args>
  void emplace(Args&&... args) {
    Locker locker(mutex);
    instance = T(std::forward<Args>(args)...);
  }

  template <class FunctionPointer>
  decltype(auto) apply(const FunctionPointer& f) {
    Locker locker(mutex);
    return f(instance);
  }

  Proxy operator->() {
    return Proxy(instance, mutex, tag);
  }

  const Proxy operator->() const {
    return Proxy(instance, mutex, tag);
  }

 private:
  class Proxy {
    T& instance;
    Locker locker;

   public:
    explicit Proxy(T& instance, Mutex& mutex, shared_wrapper_tag) :
        instance(instance),
        locker(mutex) {
    }

    ~Proxy() {
    }

    // disable_copy:
    Proxy(const Proxy&) = delete;
    Proxy& operator=(const Proxy&) = delete;

    // disable_move:
    Proxy(Proxy&&) = delete;
    Proxy& operator=(Proxy&&) = delete;

    T* operator->() {
      return &instance;
    }

    const T* operator->() const {
      return &instance;
    }
  };

  mutable Mutex mutex;
  T instance;
};

#endif // SHAREDWRAPPER_H
