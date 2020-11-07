#include "StaticBlockTag.h"

StaticBlockTag::StaticBlockTag(std::function<void()>&& f) {
  f();
}

StaticBlockTag::~StaticBlockTag() {
}
