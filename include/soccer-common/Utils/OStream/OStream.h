//
// Created by jose-cruz on 25/07/2021.
//

#ifndef SOCCER_COMMON_OSTREAM_H
#define SOCCER_COMMON_OSTREAM_H

#include <string>
#include <QDebug>
#include <optional>
#include "soccer-common/MagicEnum/MagicEnum.h"
#include "soccer-common/Utils/detail/detail.h"
#include "soccer-common/Utils/NameOfType/NameOfType.h"

#ifndef QT_NO_DEBUG_STREAM

// signatures ----------------------------------------------------------------------------------- //

namespace OStreamUtils {
  template <class OStream, class Tuple, std::size_t N>
  struct FormatTuple {
    static void print(OStream ostream, Tuple tuple);
  };

  template <class OStream, class Tuple>
  struct FormatTuple<OStream, Tuple, 1> {
    static void print(OStream ostream, Tuple tuple);
  };
} // namespace OStreamUtils

inline QDebug operator<<(QDebug dbg, const std::nullopt_t&);

template <class T>
std::enable_if_t<detail::is_streamable_v<QDebug, T>, QDebug>
operator<<(QDebug dbg, const std::optional<T>& optional);

inline QDebug operator<<(QDebug dbg, const std::monostate&);

template <class... Args>
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::variant<Args...>& variant);

template <class... Args, std::enable_if_t<sizeof...(Args) == 0, bool> = true>
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::tuple<Args...>& tuple);

template <class... Args, std::enable_if_t<sizeof...(Args) != 0, bool> = true>
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::tuple<Args...>& tuple);

inline QDebug operator<<(QDebug dbg, const std::string& str);

template <class T>
inline std::enable_if_t<std::is_enum_v<T>, QDebug> operator<<(QDebug dbg, const T& e);

// ---------------------------------------------------------------------------------------------- //

namespace OStreamUtils {
  template <class OStream, class Tuple, std::size_t N>
  void FormatTuple<OStream, Tuple, N>::print(OStream ostream, Tuple tuple) {
    FormatTuple<OStream, Tuple, N - 1>::print(ostream, tuple);
    ostream << ", " << std::get<N - 1>(tuple);
  }

  template <class OStream, class Tuple>
  void FormatTuple<OStream, Tuple, 1>::print(OStream ostream, Tuple tuple) {
    ostream << std::get<0>(tuple);
  }
} // namespace OStreamUtils

inline QDebug operator<<(QDebug dbg, const std::nullopt_t&) {
  QDebugStateSaver saver(dbg);
  dbg << "std::nullopt";
  return dbg;
}

template <class T>
std::enable_if_t<detail::is_streamable_v<QDebug, T>, QDebug>
operator<<(QDebug dbg, const std::optional<T>& optional) {
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
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::variant<Args...>& variant) {
  QDebugStateSaver saver(dbg);
  std::visit(
      [&](auto&& value) {
        dbg.nospace();
        dbg << "std::variant(" << value << ")";
      },
      variant);
  return dbg;
}

template <class... Args, std::enable_if_t<sizeof...(Args) == 0, bool>>
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::tuple<Args...>& tuple) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << "std::tuple()";
  return dbg;
}

template <class... Args, std::enable_if_t<sizeof...(Args) != 0, bool>>
std::enable_if_t<(detail::is_streamable_v<QDebug, Args> && ...), QDebug>
operator<<(QDebug dbg, const std::tuple<Args...>& tuple) {
  QDebugStateSaver saver(dbg);
  dbg.nospace();
  dbg << "std::tuple(";
  OStreamUtils::FormatTuple<decltype(dbg), decltype(tuple), sizeof...(Args)>::print(dbg, tuple);
  dbg << ")";
  return dbg;
}

inline QDebug operator<<(QDebug dbg, const std::string& str) {
  QDebugStateSaver saver(dbg);
  dbg << QString::fromStdString(str);
  return dbg;
}

template <class T>
inline std::enable_if_t<std::is_enum_v<T>, QDebug> operator<<(QDebug dbg, const T& e) {
  QDebugStateSaver saver(dbg);
  dbg << MagicEnum::name(e);
  return dbg;
}

#endif // QT_NO_DEBUG_STREAM

#endif // SOCCER_COMMON_OSTREAM_H
