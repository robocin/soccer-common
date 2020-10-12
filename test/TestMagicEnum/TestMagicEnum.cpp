#include "TestMagicEnum.h"

void TestMagicEnum::initTestCase() {
}

void TestMagicEnum::init() {
}

void TestMagicEnum::cleanup() {
}

void TestMagicEnum::cleanupTestCase() {
}

void TestMagicEnum::testCast() {
  auto op1 = MagicEnum::cast<EnumNormal>("ValueEN_A", [](char a, char b) {
    return tolower(a) == tolower(b);
  });
  if (op1) {
    qDebug() << op1.value();
  }
  auto op2 = MagicEnum::cast<EnumNormal>(0ll);
  if (op2) {
    qDebug() << op2.value();
  }
}

QTEST_MAIN(TestMagicEnum)
