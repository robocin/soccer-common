#ifndef SOCCER_COMMON_CTOR_H
#define SOCCER_COMMON_CTOR_H

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define RC_CTOR_1(type)                                                                            \
 public:                                                                                           \
  inline type() = default

#define RC_CTOR_2(type, var1)                                                                      \
 public:                                                                                           \
  inline explicit type(decltype(m_##var1) var1) : m_##var1(var1) {                                 \
  }

#define RC_CTOR_3(type, var1, var2)                                                                \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1, decltype(m_##var2) var2) : m_##var1(var1), m_##var2(var2) { \
  }

#define RC_CTOR_4(type, var1, var2, var3)                                                          \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1, decltype(m_##var2) var2, decltype(m_##var3) var3) :         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3) {                                                                             \
  }

#define RC_CTOR_5(type, var1, var2, var3, var4)                                                    \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4) {                                                                             \
  }

#define RC_CTOR_6(type, var1, var2, var3, var4, var5)                                              \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5) {                                                                             \
  }

#define RC_CTOR_7(type, var1, var2, var3, var4, var5, var6)                                        \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6) {                                                                             \
  }

#define RC_CTOR_8(type, var1, var2, var3, var4, var5, var6, var7)                                  \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7) {                                                                             \
  }

#define RC_CTOR_9(type, var1, var2, var3, var4, var5, var6, var7, var8)                            \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8) {                                                                             \
  }

#define RC_CTOR_10(type, var1, var2, var3, var4, var5, var6, var7, var8, var9)                     \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9) :                                                           \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9) {                                                                             \
  }

#define RC_CTOR_11(type, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10)              \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10) {                                                                           \
  }

#define RC_CTOR_12(type, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11)       \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10,                                                           \
              decltype(m_##var11) var11) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10),                                                                            \
      m_##var11(var11) {                                                                           \
  }

#define RC_CTOR_13(type,                                                                           \
                   var1,                                                                           \
                   var2,                                                                           \
                   var3,                                                                           \
                   var4,                                                                           \
                   var5,                                                                           \
                   var6,                                                                           \
                   var7,                                                                           \
                   var8,                                                                           \
                   var9,                                                                           \
                   var10,                                                                          \
                   var11,                                                                          \
                   var12)                                                                          \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10,                                                           \
              decltype(m_##var11) var11,                                                           \
              decltype(m_##var12) var12) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10),                                                                            \
      m_##var11(var11),                                                                            \
      m_##var12(var12) {                                                                           \
  }

#define RC_CTOR_14(type,                                                                           \
                   var1,                                                                           \
                   var2,                                                                           \
                   var3,                                                                           \
                   var4,                                                                           \
                   var5,                                                                           \
                   var6,                                                                           \
                   var7,                                                                           \
                   var8,                                                                           \
                   var9,                                                                           \
                   var10,                                                                          \
                   var11,                                                                          \
                   var12,                                                                          \
                   var13)                                                                          \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10,                                                           \
              decltype(m_##var11) var11,                                                           \
              decltype(m_##var12) var12,                                                           \
              decltype(m_##var13) var13) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10),                                                                            \
      m_##var11(var11),                                                                            \
      m_##var12(var12),                                                                            \
      m_##var13(var13) {                                                                           \
  }

#define RC_CTOR_15(type,                                                                           \
                   var1,                                                                           \
                   var2,                                                                           \
                   var3,                                                                           \
                   var4,                                                                           \
                   var5,                                                                           \
                   var6,                                                                           \
                   var7,                                                                           \
                   var8,                                                                           \
                   var9,                                                                           \
                   var10,                                                                          \
                   var11,                                                                          \
                   var12,                                                                          \
                   var13,                                                                          \
                   var14)                                                                          \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10,                                                           \
              decltype(m_##var11) var11,                                                           \
              decltype(m_##var12) var12,                                                           \
              decltype(m_##var13) var13,                                                           \
              decltype(m_##var14) var14) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10),                                                                            \
      m_##var11(var11),                                                                            \
      m_##var12(var12),                                                                            \
      m_##var13(var13),                                                                            \
      m_##var14(var14) {                                                                           \
  }

#define RC_CTOR_16(type,                                                                           \
                   var1,                                                                           \
                   var2,                                                                           \
                   var3,                                                                           \
                   var4,                                                                           \
                   var5,                                                                           \
                   var6,                                                                           \
                   var7,                                                                           \
                   var8,                                                                           \
                   var9,                                                                           \
                   var10,                                                                          \
                   var11,                                                                          \
                   var12,                                                                          \
                   var13,                                                                          \
                   var14,                                                                          \
                   var15)                                                                          \
 public:                                                                                           \
  inline type(decltype(m_##var1) var1,                                                             \
              decltype(m_##var2) var2,                                                             \
              decltype(m_##var3) var3,                                                             \
              decltype(m_##var4) var4,                                                             \
              decltype(m_##var5) var5,                                                             \
              decltype(m_##var6) var6,                                                             \
              decltype(m_##var7) var7,                                                             \
              decltype(m_##var8) var8,                                                             \
              decltype(m_##var9) var9,                                                             \
              decltype(m_##var10) var10,                                                           \
              decltype(m_##var11) var11,                                                           \
              decltype(m_##var12) var12,                                                           \
              decltype(m_##var13) var13,                                                           \
              decltype(m_##var14) var14,                                                           \
              decltype(m_##var15) var15) :                                                         \
      m_##var1(var1),                                                                              \
      m_##var2(var2),                                                                              \
      m_##var3(var3),                                                                              \
      m_##var4(var4),                                                                              \
      m_##var5(var5),                                                                              \
      m_##var6(var6),                                                                              \
      m_##var7(var7),                                                                              \
      m_##var8(var8),                                                                              \
      m_##var9(var9),                                                                              \
      m_##var10(var10),                                                                            \
      m_##var11(var11),                                                                            \
      m_##var12(var12),                                                                            \
      m_##var13(var13),                                                                            \
      m_##var14(var14),                                                                            \
      m_##var15(var15) {                                                                           \
  }

#if !BOOST_PP_VARIADICS_MSVC
  #define RC_CTOR(...) BOOST_PP_OVERLOAD(RC_CTOR_, __VA_ARGS__)(__VA_ARGS__)
#else
  #define RC_CTOR(...)                                                                             \
    BOOST_PP_CAT(BOOST_PP_OVERLOAD(RC_CTOR_, __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())
#endif

#ifndef SOCCER_COMMON_CTOR_UNDEF
  #define CTOR(...) RC_CTOR(__VA_ARGS__)
#endif

#endif // SOCCER_COMMON_CTOR_H
