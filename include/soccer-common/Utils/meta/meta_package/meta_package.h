#ifndef SOCCER_COMMON_META_PACKAGE_H
#define SOCCER_COMMON_META_PACKAGE_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <optional>

/*!
 * @brief This macro advertises and helps to create a package
 * (setter-builder/getter class) using only metaprogramming
 */
#define RC_META_PACKAGE(type) class [[nodiscard]] [[maybe_unused]] type

/*!
 * @brief declares a private type with name 'varname', initialized with value, and its own public
 * static get method
 */
#define RC_CTE(type, varname, value)                                                               \
 public:                                                                                           \
  static constexpr const type& varname() {                                                         \
    return m_##varname;                                                                            \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
  static constexpr type m_##varname = {value}

/*!
 * @brief declares a private type with name 'varname', default_value
 * initialized, and its own public set/get methods
 */
#define RC_VAR(type, varname)                                                                      \
 public:                                                                                           \
  inline auto set_##varname(const type& varname)->decltype(*this)& {                               \
    m_##varname = varname;                                                                         \
    return *this;                                                                                  \
  }                                                                                                \
  template <class... Args>                                                                         \
  inline auto emplace_##varname(Args&&... args)->decltype(*this)& {                                \
    m_##varname = type(std::forward<Args>(args)...);                                               \
    return *this;                                                                                  \
  }                                                                                                \
  inline const type& varname() const {                                                             \
    return m_##varname;                                                                            \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
  type m_##varname {                                                                               \
  }

/*!
 * @brief declares a private type with name 'varname', given default value, and
 * its own public set/get methods
 */
#define RC_VARVAL(type, varname, default_value)                                                    \
 public:                                                                                           \
  inline auto set_##varname(const type& varname)->decltype(*this)& {                               \
    m_##varname = varname;                                                                         \
    return *this;                                                                                  \
  }                                                                                                \
  template <class... Args>                                                                         \
  inline auto emplace_##varname(Args&&... args)->decltype(*this)& {                                \
    m_##varname = type(std::forward<Args>(args)...);                                               \
    return *this;                                                                                  \
  }                                                                                                \
  inline const type& varname() const {                                                             \
    return m_##varname;                                                                            \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
  type m_##varname = {default_value}

/*!
 * @brief declares a private type with varname and its own public set/get
 * methods
 * @note varname will be wrapped by a std::optional, so, it's useful to use this
 * macro with types that doesn't contains empty constructors or with variables
 * that empty constructor doesn't make sense
 */
#define RC_VAROPT(type, varname)                                                                   \
 public:                                                                                           \
  inline auto set_##varname(const type& varname)->decltype(*this)& {                               \
    m_##varname = varname;                                                                         \
    return *this;                                                                                  \
  }                                                                                                \
  inline auto set_##varname(const std::optional<type>& varname)->decltype(*this)& {                \
    m_##varname = varname;                                                                         \
    return *this;                                                                                  \
  }                                                                                                \
  template <class... Args>                                                                         \
  inline auto emplace_##varname(Args&&... args)->decltype(*this)& {                                \
    m_##varname.emplace(std::forward<Args>(args)...);                                              \
    return *this;                                                                                  \
  }                                                                                                \
  inline bool has_##varname() const {                                                              \
    return m_##varname.has_value();                                                                \
  }                                                                                                \
  inline const std::optional<type>& optional_##varname() const {                                   \
    return m_##varname;                                                                            \
  }                                                                                                \
  inline const type& varname() const {                                                             \
    try {                                                                                          \
      return m_##varname.value();                                                                  \
    } catch (const std::bad_optional_access&) {                                                    \
      throw;                                                                                       \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
  std::optional<type> m_##varname

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_META_PACKAGE_H
