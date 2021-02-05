#ifndef SOCCER_COMMON_SINGLETON_H
#define SOCCER_COMMON_SINGLETON_H

template <class T>
class Singleton {
  Singleton() = default;

 public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

  static T& instance() {
    static T value;
    return value;
  }
};

template <class T>
using singleton_t [[maybe_unused]] = Singleton<T>;

template <class T>
[[maybe_unused]] inline static T& singleton_v = Singleton<T>::instance();

#endif // SOCCER_COMMON_SINGLETON_H
