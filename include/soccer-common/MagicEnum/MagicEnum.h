#ifndef SOCCER_COMMON_MAGICENUM_H
#define SOCCER_COMMON_MAGICENUM_H

#include <QVector>
#include <QString>
#include <optional>
#include <QStringList>
#include <magic_enum.hpp>

namespace MagicEnum {
  template <class E, class BinaryPredicate>
  constexpr std::optional<std::decay_t<E>> cast(const QString& value, BinaryPredicate&& p) {
    return magic_enum::enum_cast<E, BinaryPredicate>(value.toStdString(),
                                                     std::forward<BinaryPredicate>(p));
  }

  template <class E, class T>
  constexpr std::optional<std::decay_t<E>> cast(const T& value) {
    if constexpr (std::is_base_of_v<QString, T>) {
      return magic_enum::enum_cast<E>(value.toStdString());
    } else {
      return magic_enum::enum_cast<E>(value);
    }
  }

  template <class E>
  constexpr std::decay_t<E> valueAt(int index) {
    return magic_enum::enum_value<E>(static_cast<std::size_t>(index));
  }

  template <class E>
  QVector<E> values() {
    constexpr auto v = magic_enum::enum_values<E>();
    QVector<E> ret(v.begin(), v.end());
    return ret;
  }

  template <class E>
  constexpr int count() {
    return static_cast<int>(magic_enum::enum_count<E>());
  }

  template <class E>
  constexpr decltype(auto) integer(const E& value) {
    return magic_enum::enum_integer<E>(value);
  }

  template <auto V>
  QString name() {
    static_assert(std::is_enum_v<decltype(V)>);
    return magic_enum::enum_name<V>().data();
  }

  template <class E>
  QString name(const E& value) {
    return magic_enum::enum_name<E>(value).data();
  }

  template <class E>
  QStringList names() {
    constexpr auto v = magic_enum::enum_names<E>();
    QStringList ret;
    for (const auto& str : v) {
      ret += str.data();
    }
    return ret;
  }

  template <class E>
  QMap<E, QString> entries() {
    constexpr auto m = magic_enum::enum_entries<E>();
    QMap<E, QString> entries;
    for (const auto& [first, second] : m) {
      entries.insert(first, second.data());
    }
    return entries;
  }

  template <class E>
  constexpr std::optional<int> index(const E& value) {
    return static_cast<std::optional<int>>(magic_enum::enum_index<E>(value));
  }

  template <class E>
  constexpr bool contains(const E& value) {
    return magic_enum::enum_contains<E>(value);
  }

  template <class E>
  constexpr bool contains(magic_enum::underlying_type_t<E> value) {
    return magic_enum::enum_contains<E>(value);
  }

  template <class E>
  constexpr bool contains(const QString& value) {
    return magic_enum::enum_contains<E>(value.toStdString());
  }
}; // namespace MagicEnum

#endif // SOCCER_COMMON_MAGICENUM_H
