#ifndef SOCCER_COMMON_STATICBLOCKTAG_H
#define SOCCER_COMMON_STATICBLOCKTAG_H

#include <functional>

struct StaticBlockTag {
  StaticBlockTag(std::function<void(void)>&& f);

  StaticBlockTag(const StaticBlockTag&) = delete;
  StaticBlockTag& operator=(const StaticBlockTag&) = delete;

  StaticBlockTag(StaticBlockTag&&) = delete;
  StaticBlockTag& operator=(StaticBlockTag&&) = delete;

  ~StaticBlockTag();
};

#define __RC_TOKEN_PASTING(A, B) __RC_TOKEN_PASTING_(A, B)
#define __RC_TOKEN_PASTING_(A, B) A##B

#define static_block                                                           \
  inline static const auto& __RC_TOKEN_PASTING(                                \
      __RC_TOKEN_PASTING(__RC_TOKEN_PASTING(static_block_tag_, __COUNTER__),   \
                         _at_line_),                                           \
      __LINE__) = (StaticBlockTag)[]()->void

#endif // SOCCER_COMMON_STATICBLOCKTAG_H
