#include "TestMagicEnum.h"

TestMagicEnum::TestMagicEnum() {
}

TestMagicEnum::~TestMagicEnum() {
}

void TestMagicEnum::initTestCase() {
}

void TestMagicEnum::init() {
}

void TestMagicEnum::cleanup() {
}

void TestMagicEnum::cleanupTestCase() {
}

void TestMagicEnum::test_cast_WithGivenABinaryPredicate_ShouldFindValue() {
  auto op1 = MagicEnum::cast<EnumNormal>("ValueEN_A", [](char a, char b) {
    return tolower(a) == tolower(b);
  });
  QVERIFY(op1.has_value());
  auto op2 = MagicEnum::cast<EnumNormal>(0ll);
  QVERIFY(op2.has_value());
}

QTEST_MAIN(TestMagicEnum)
