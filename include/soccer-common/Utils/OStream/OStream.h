//
// Created by jose-cruz on 25/07/2021.
//

#ifndef SOCCER_COMMON_OSTREAM_H
#define SOCCER_COMMON_OSTREAM_H

#include <QDebug>
#include <optional>
#include "soccer-common/Utils/NameOfType/NameOfType.h"

#ifndef QT_NO_DEBUG_STREAM

namespace OStreamUtils {
  template <class OStream, class Tuple, std::size_t N>
  struct FormatTuple {
    static void print(OStream ostream, Tuple tuple) {
      FormatTuple<OStream, Tuple, N - 1>::print(ostream, tuple);
      ostream << ", " << std::get<N - 1>(tuple);
    }
  };

  template <class OStream, class Tuple>
  struct FormatTuple<OStream, Tuple, 1> {
    static void print(OStream ostream, Tuple tuple) {
      ostream << std::get<0>(tuple);
    }
  };
} // namespace OStreamUtils

inline QDebug operator<<(QDebug dbg, const std::nullopt_t&) {
  QDebugStateSaver saver(dbg);
  dbg << "std::nullopt";
  return dbg;
}

template <class T>
QDebug operator<<(QDebug dbg, const std::optional<T>& optional) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  if (optional) {
    dbg << "std::optional(" << optional.value() << ")";
  } else {
    dbg << std::nullopt;
  }
  return dbg;
}

inline QDebug operator<<(QDebug dbg, const std::monostate&) {
  QDebugStateSaver saver(dbg);
  dbg << "std::monostate()";
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

template <class... Args, std::enable_if_t<sizeof...(Args) == 0, bool> = true>
QDebug operator<<(QDebug dbg, const std::tuple<Args...>& tuple) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << "std::tuple()";
  return dbg;
}

template <class... Args, std::enable_if_t<sizeof...(Args) != 0, bool> = true>
QDebug operator<<(QDebug dbg, const std::tuple<Args...>& tuple) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << "std::tuple(";
  OStreamUtils::FormatTuple<decltype(dbg), decltype(tuple), sizeof...(Args)>::print(dbg, tuple);
  dbg << ")";
  return dbg;
}

#endif

#endif // SOCCER_COMMON_OSTREAM_H
