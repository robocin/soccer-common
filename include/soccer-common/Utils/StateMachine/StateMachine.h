//
// Created by jose-cruz on 08/05/2022.
//

#ifndef SOCCER_COMMON_STATEMACHINE_H
#define SOCCER_COMMON_STATEMACHINE_H

#include <utility>
#include "soccer-common/Utils/Concept/Concept.h"
#include "soccer-common/Utils/overloaded_visitor_t/overloaded_visitor_t.h"

template <Concept::Variant State, class... Functors>
class StateMachine {
  static_assert(sizeof...(Functors) > 0);
  static_assert(Concept::MatchingVisitor<overloaded_visitor_t<Functors...>, State>);

  template <class T, class F, class... Fs>
  static constexpr auto PointerToMatchingFunctorDeclval() {
    if constexpr (Concept::MatchingFunctor<F, T>) {
      return static_cast<F*>(nullptr);
    } else if (sizeof...(Fs) > 0) {
      return PointerToMatchingFunctorDeclval<T, Fs...>();
    } else {
      static_assert(sizeof...(Fs) > 0, "no matching functor was found for the given type.");
    }
  }

  template <class T, class... Fs>
  using MatchingFunctorForType = std::remove_pointer_t<
      std::invoke_result_t<decltype(PointerToMatchingFunctorDeclval<T, Fs...>)>>;

 public:
  using return_type = decltype(
      std::visit(std::declval<overloaded_visitor_t<Functors...>>(), std::declval<State>()));

  StateMachine() requires(std::default_initializable<State>) = default;

  template <class... Args>
  explicit StateMachine(State state, Args&&... args) :
      last{std::move(state)},
      visitor{std::forward<Args>(args)...} {
  }

  return_type operator()(State state) {
    return_type output = std::visit(visitor, state);
    if (last.index() != state.index()) {
      clear();
    }
    last = std::move(state);
    return output;
  }

  [[nodiscard]] const State& currentState() const {
    return last;
  }

  void clear() {
    std::visit(
        [&](auto&& state) {
          using T = std::decay_t<decltype(state)>;
          using F = MatchingFunctorForType<T, Functors...>;
          if constexpr (Concept::Cleanable<F>) {
            static_cast<F&>(visitor).clear();
          }
        },
        last);
  }

  void reset(State state) {
    clear();
    last = std::move(state);
  }

 protected:
  State last;
  overloaded_visitor_t<Functors...> visitor{};
};

template <class T>
class SpecializedNode {
  template <class...>
  static constexpr bool dependent_false_v = false;

  static_assert(dependent_false_v<T>, "this node has to be specialized.");
};

namespace {
  template <class T>
  struct InjectedStateMachineImpl {};

  template <class... Args>
  struct InjectedStateMachineImpl<std::variant<Args...>> {
    using type = StateMachine<std::variant<Args...>, SpecializedNode<Args>...>;
  };

  template <Concept::Variant State>
  using InjectedStateMachine = typename InjectedStateMachineImpl<State>::type;
} // namespace

template <Concept::Variant State>
class StateMachine<State> : public InjectedStateMachine<State> {
 public:
  using return_type = typename InjectedStateMachine<State>::return_type;

  using InjectedStateMachine<State>::InjectedStateMachine;
  using InjectedStateMachine<State>::operator();
  using InjectedStateMachine<State>::currentState;
  using InjectedStateMachine<State>::clear;
  using InjectedStateMachine<State>::reset;
};

template <Concept::Variant State>
class ImplicitStateMachine : public StateMachine<State> {
  static_assert(Concept::Pair<typename StateMachine<State>::return_type>);
  static_assert(std::same_as<State, typename StateMachine<State>::return_type::first_type>);

 public:
  using return_type = typename StateMachine<State>::return_type::second_type;

  template <class... Args>
  explicit ImplicitStateMachine(State state, Args&&... args) :
      StateMachine<State>{std::move(state), std::forward<Args>(args)...} {
  }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
  return_type operator()(State state) {
    if (this->last.index() != state.index()) {
      clear();
    }
    this->last = std::move(state);
    return operator()();
  }
#pragma clang diagnostic pop

  return_type operator()() {
    auto [next, result] = std::visit(this->visitor, this->last);
    if (this->last.index() != next.index()) {
      clear();
    }
    this->last = std::move(next);
    return result;
  }

  using StateMachine<State>::currentState;
  using StateMachine<State>::clear;
  using StateMachine<State>::reset;
};

template <class Output, class Input>
struct VisitorForwarderBase {
  inline Output operator()(Input input) {
    return Output(std::move(input));
  }

  inline Output operator()(Input input) const {
    return Output(std::move(input));
  }
};

template <class Output, class... Inputs>
struct VisitorForwarder : public VisitorForwarderBase<Output, Inputs>... {
  static_assert(sizeof...(Inputs) > 0, "at least one input is required.");

  template <class... Placeholders>
  inline explicit VisitorForwarder(Placeholders&&...) {
  }

  using VisitorForwarderBase<Output, Inputs>::operator()...;
};

#endif // SOCCER_COMMON_STATEMACHINE_H
