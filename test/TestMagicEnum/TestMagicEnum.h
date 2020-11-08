#include <QtTest>

#include "soccer-common/MagicEnum/MagicEnum.h"

class TestMagicEnum : public QObject {
  Q_OBJECT

  enum EnumNormal { ValueEN_A = -1, ValueEN_B, ValueEN_C };

  enum class EnumClass { ValueEC_A = -2, ValueEC_B, ValueEC_C };

  enum { ValueEUnnamed_A = -3, ValueEUnnamed_B, ValueEUnnamed_C };

 public:
  TestMagicEnum();
  ~TestMagicEnum();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void testCast();
};
