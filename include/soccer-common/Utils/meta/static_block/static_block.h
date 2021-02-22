#ifndef SOCCER_COMMON_STATIC_BLOCK_H
#define SOCCER_COMMON_STATIC_BLOCK_H

#include <utility>

namespace __rc_meta { // NOLINT(bugprone-reserved-identifier)
  struct [[nodiscard]] [[maybe_unused]] static_block_tag {
    template <class Functor>
    inline explicit static_block_tag(Functor && f) {
      std::forward<Functor>(f)();
    }
    ~static_block_tag() = default;

    // disable_copy:
    static_block_tag(const static_block_tag&) = delete;
    static_block_tag& operator=(const static_block_tag&) = delete;

    // disable_move:
    static_block_tag(static_block_tag &&) = delete;
    static_block_tag& operator=(static_block_tag&&) = delete;
  };
} // namespace __rc_meta

#define __RC_TOKEN_PASTING__(A, B) __RC_TOKEN_PASTING_IMPL__(A, B)
#define __RC_TOKEN_PASTING_IMPL__(A, B) A##B

#define __static_block_declaration__                                                               \
  inline static const auto __RC_TOKEN_PASTING__(                                                   \
      __RC_TOKEN_PASTING__(__RC_TOKEN_PASTING__(static_block_tag_, __COUNTER__), _at_line_),       \
      __LINE__) = (__rc_meta::static_block_tag)[]()->void

#define static_block __static_block_declaration__ // NOLINT(cert-err58-cpp)

#endif // SOCCER_COMMON_STATIC_BLOCK_H
