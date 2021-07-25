//
// Created by jose-cruz on 25/07/2021.
//

#ifndef SOCCER_COMMON_OSTREAM_H
#define SOCCER_COMMON_OSTREAM_H

#include <QDebug>
#include <optional>
#include "soccer-common/Utils/NameOfType/NameOfType.h"

#ifndef QT_NO_DEBUG_STREAM
template <class T>
QDebug operator<<(QDebug dbg, const std::optional<T>& optional) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  if (optional) {
    dbg << "std::optional(" << optional.value() << ")";
  } else {
    dbg << "nullopt";
  }
  return dbg;
}

template <class... Args>
QDebug operator<<(QDebug dbg, const std::variant<Args...>& variant) {
  QDebugStateSaver saver(dbg);
  std::visit(
      [&](auto&& value) {
        dbg.nospace();
        dbg << "std::variant(" << value << ")";
      },
      variant);
  return dbg;
}
#endif

#endif // SOCCER_COMMON_OSTREAM_H
