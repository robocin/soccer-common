#ifndef SOCCER_COMMON_SINGLETON_H
#define SOCCER_COMMON_SINGLETON_H

template <class T>
class Singleton {
  Singleton();

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
using singleton_t = Singleton<T>;

template <class T>
inline static T& singleton_v = Singleton<T>::instance();

#endif // SOCCER_COMMON_SINGLETON_H
