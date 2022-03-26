#ifndef SOCCER_COMMON_OVERLOADED_VISITOR_T_H
#define SOCCER_COMMON_OVERLOADED_VISITOR_T_H

#include <utility>

template <class... Ts>
class overloaded_visitor_t : public Ts... {
 public:
  using Ts::operator()...;

  template <class... Args>
  explicit overloaded_visitor_t(Args&&... args) : Ts{std::forward<Args>(args)...}... {
  }
};

#endif // SOCCER_COMMON_OVERLOADED_VISITOR_T_H
