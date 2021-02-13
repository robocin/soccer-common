#ifndef SOCCER_COMMON_STATICBLOCKTAG_H
#define SOCCER_COMMON_STATICBLOCKTAG_H

#include <functional>

struct [[nodiscard]] [[maybe_unused]] static_block_tag {
  template <class Functor>
  inline explicit static_block_tag(Functor&& f) {
    std::forward<Functor>(f)();
  }
  ~static_block_tag() = default;

  // disable_copy:
  static_block_tag(const static_block_tag&) = delete;
  static_block_tag& operator=(const static_block_tag&) = delete;

  // disable_move:
  static_block_tag(static_block_tag&&) = delete;
  static_block_tag& operator=(static_block_tag&&) = delete;
};

#define __RC_TOKEN_PASTING__(A, B) __RC_TOKEN_PASTING_IMPL__(A, B)
#define __RC_TOKEN_PASTING_IMPL__(A, B) A##B

#define static_block                                                           \
  inline static const auto __RC_TOKEN_PASTING__(                               \
      __RC_TOKEN_PASTING__(                                                    \
          __RC_TOKEN_PASTING__(static_block_tag_, __COUNTER__),                \
          _at_line_),                                                          \
      __LINE__) = (static_block_tag)[]()->void

#endif // SOCCER_COMMON_STATICBLOCKTAG_H
