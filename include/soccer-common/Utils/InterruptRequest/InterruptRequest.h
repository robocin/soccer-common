#ifndef SOCCER_COMMON_INTERRUPTREQUEST_H
#define SOCCER_COMMON_INTERRUPTREQUEST_H

#include <atomic>
#include <csignal>
#include <stdexcept>
#include <functional>

template <int I>
class InterruptRequest {
  template <int V>
  static constexpr bool dependent_false_v = false;

  static constexpr const char* m_message = []() -> const char* {
    if constexpr (I == SIGTERM) {
      return "termination request.";
    } else if constexpr (I == SIGSEGV) {
      return "invalid memory access (segmentation fault).";
    } else if constexpr (I == SIGINT) {
      return "external interrupt.";
    } else if constexpr (I == SIGILL) {
      return "invalid program image.";
    } else if constexpr (I == SIGABRT) {
      return "abnormal termination condition.";
    } else if constexpr (I == SIGFPE) {
      return "erroneous arithmetic operation.";
    } else {
      static_assert(dependent_false_v<I>, "unknown interrupt.");
    }
  }();

 public:
  template <class F>
  static void setup(F f) {
    static std::atomic<bool> initialized = false;
    static std::function<void()> function = nullptr;
    if (initialized) {
      throw std::runtime_error("cannot setup twice.");
    } else {
      initialized = true;
      function = f;
    }
    std::signal(I, [](int s) {
      if (function) {
        function();
      } else /* natural behavior */ {
        std::exit(128 + s);
      }
    });
  }

  static constexpr const char* message() {
    return m_message;
  }
};

#endif // SOCCER_COMMON_INTERRUPTREQUEST_H
