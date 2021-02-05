#ifndef SOCCER_COMMON_STATICBLOCKTAG_H
#define SOCCER_COMMON_STATICBLOCKTAG_H

#include <functional>

struct StaticBlockTag {
  template <class Functor>
  inline explicit StaticBlockTag(Functor&& f) {
    std::forward<Functor>(f)();
  }
  ~StaticBlockTag() = default;

  // disable_copy:
  StaticBlockTag(const StaticBlockTag&) = delete;
  StaticBlockTag& operator=(const StaticBlockTag&) = delete;

  // disable_move:
  StaticBlockTag(StaticBlockTag&&) = delete;
  StaticBlockTag& operator=(StaticBlockTag&&) = delete;
};

#define __RC_TOKEN_PASTING__(A, B) __RC_TOKEN_PASTING_IMPL__(A, B)
#define __RC_TOKEN_PASTING_IMPL__(A, B) A##B

#define static_block                                                           \
  inline static const auto __RC_TOKEN_PASTING__(                               \
      __RC_TOKEN_PASTING__(                                                    \
          __RC_TOKEN_PASTING__(static_block_tag_, __COUNTER__),                \
          _at_line_),                                                          \
      __LINE__) = (StaticBlockTag)[]()->void

#endif // SOCCER_COMMON_STATICBLOCKTAG_H
