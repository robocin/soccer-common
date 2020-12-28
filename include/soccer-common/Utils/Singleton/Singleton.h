#ifndef SINGLETON_H
#define SINGLETON_H

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
inline static T& singleton_v = Singleton<T>::instance();

#endif // SINGLETON_H
