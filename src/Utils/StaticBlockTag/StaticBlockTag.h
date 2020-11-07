#ifndef STATICBLOCKTAG_H
#define STATICBLOCKTAG_H

#include <functional>

struct StaticBlockTag {
  StaticBlockTag(std::function<void(void)>&& f);

  StaticBlockTag(const StaticBlockTag&) = delete;
  StaticBlockTag& operator=(const StaticBlockTag&) = delete;

  StaticBlockTag(StaticBlockTag&&) = delete;
  StaticBlockTag& operator=(StaticBlockTag&&) = delete;

  ~StaticBlockTag();
};

#define TOKEN_PASTING(A, B) TOKEN_PASTING_(A, B)
#define TOKEN_PASTING_(A, B) A##B

#define static_block                                                           \
  inline static const auto& TOKEN_PASTING(                                     \
      TOKEN_PASTING(TOKEN_PASTING(static_block_tag_, __COUNTER__), _at_line_), \
      __LINE__) = (StaticBlockTag)[]()->void

#endif // STATICBLOCKTAG_H
