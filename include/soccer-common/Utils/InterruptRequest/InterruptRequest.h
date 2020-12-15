#ifndef INTERRUPTREQUEST_H
#define INTERRUPTREQUEST_H

#include <atomic>
#include <csignal>
#include <iostream>
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

  inline static std::atomic<bool> initialized;
  inline static std::function<void()> m_function;

 public:
  template <class F>
  static void setup(F f) {
    if (initialized) {
      throw std::runtime_error("cannot setup twice.");
    } else {
      initialized = true;
      m_function = f;
    }
    std::signal(I, [](int s) {
      std::cout << "signal called after interrupt (code: " << s << ")"
                << std::endl;
      std::cout << "  message(): " << message() << std::endl << std::endl;
      if (m_function) {
        m_function();
      } else /* natural behavior */ {
        std::exit(128 + s);
      }
    });
  }

  static constexpr const char* message() {
    return m_message;
  }
};

#endif // INTERRUPTREQUEST_H
