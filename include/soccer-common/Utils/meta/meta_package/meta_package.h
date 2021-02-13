#ifndef SOCCER_COMMON_META_PACKAGE_H
#define SOCCER_COMMON_META_PACKAGE_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <iostream>
#include <optional>

/*!
 * @brief This macro advertises and helps to create a package (setter/getter
 * class) using only metaprogramming
 */
#define RC_META_PACKAGE(type) class [[nodiscard]] [[maybe_unused]] type

/*!
 * @brief declares a private type with varname, and its own public set/get
 * methods
 */
#define RC_VAR(type, varname)                                                  \
 public:                                                                       \
  inline auto set##varname(const type& t##varname)->decltype(*this)& {         \
    m##varname = t##varname;                                                   \
    return *this;                                                              \
  }                                                                            \
  inline const type& get##varname() const {                                    \
    return m##varname;                                                         \
  }                                                                            \
                                                                               \
 private:                                                                      \
  type m##varname

/*!
 * @brief declares a private type with varname, default value, and its own
 * public set/get methods
 */
#define RC_VARVAL(type, varname, default_value)                                \
 public:                                                                       \
  inline auto set##varname(const type& t##varname)->decltype(*this)& {         \
    m##varname = t##varname;                                                   \
    return *this;                                                              \
  }                                                                            \
  inline const type& get##varname() const {                                    \
    return m##varname;                                                         \
  }                                                                            \
                                                                               \
 private:                                                                      \
  type m##varname = {default_value}

/*!
 * @brief declares a private type with varname and its own public set/get
 * methods
 * @note varname will be wrapped by a std::optional, so, it's useful to use this
 * macro with types that doesn't contains empty constructors or with variables
 * that empty constructor doesn't make sense
 */
#define RC_VAROPT(type, varname)                                               \
 public:                                                                       \
  inline auto set##varname(const type& t##varname)->decltype(*this)& {         \
    m##varname = t##varname;                                                   \
    return *this;                                                              \
  }                                                                            \
  inline const type& get##varname() const {                                    \
    try {                                                                      \
      return m##varname.value();                                               \
    } catch (const std::bad_optional_access&) {                                \
      throw;                                                                   \
    }                                                                          \
  }                                                                            \
                                                                               \
 private:                                                                      \
  std::optional<type> m##varname

#pragma clang diagnostic pop

#endif // SSL_UNIFICATION_META_PACKAGE_H
