#ifndef SOCCER_COMMON_META_PACKAGE_H
#define SOCCER_COMMON_META_PACKAGE_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#include <optional>
#include <stdexcept>

#include "soccer-common/Utils/NameOfType/NameOfType.h"

/*!
 * @brief declares a private type with varname and its own public set/get
 * methods
 * @note varname will be wrapped by a std::optional, so, it's useful to use this
 * macro with types that doesn't contains empty constructors or with variables
 * that empty constructor doesn't make sense
 */
#define RC_PROPERTY_2(type, varname)                                                               \
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
      throw std::runtime_error(                                                                    \
          ("the field \'" + Utils::nameOfType<std::decay_t<decltype(*this)>>() +                   \
           "::" + QString(#varname) + "()\' is std::nullopt (bad optional access).")               \
              .toStdString());                                                                     \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
 private:                                                                                          \
  std::optional<type> m_##varname

/*!
 * @brief declares a private type with name 'varname', given default value, and
 * its own public set/get methods
 */
#define RC_PROPERTY_3(type, varname, default_value)                                                \
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
  type m_##varname = default_value

#if !BOOST_PP_VARIADICS_MSVC
  #define RC_PROPERTY(...) BOOST_PP_OVERLOAD(RC_PROPERTY_, __VA_ARGS__)(__VA_ARGS__)
#else
  #define RC_PROPERTY(...)                                                                         \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD(RC_PROPERTY_, __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())
#endif

#ifndef SOCCER_COMMON_PROPERTY_UNDEF
  #define PROPERTY(...) RC_PROPERTY(__VA_ARGS__)
#endif

#include "ctor.h"

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_META_PACKAGE_H
