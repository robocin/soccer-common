#include "TestUtils.h"

TestUtils::TestUtils() {
}

TestUtils::~TestUtils() {
}

void TestUtils::initTestCase() {
}

void TestUtils::init() {
}

void TestUtils::cleanup() {
}

void TestUtils::cleanupTestCase() {
}

void TestUtils::test_nameOfType_WithGivenType_ShouldWork() {
  QCOMPARE(Utils::nameOfType<integer>(), "int");
  QCOMPARE(Utils::nameOfType<real>(), "double");

  QCOMPARE(Utils::nameOfType<Struct1>(), "TestUtils::Struct1");

  QCOMPARE(Utils::nameOfType<int&>(), "int&");

  QCOMPARE(Utils::nameOfType<float&&>(), "float&&");

  QCOMPARE(Utils::nameOfType<const char*>(), "const char*");

  QCOMPARE((Utils::nameOfType<std::pair<int, int>>()), "std::pair<int, int>");
  QCOMPARE((Utils::nameOfType<pair<int, int>>()), "std::pair<int, int>");
}

void TestUtils::test_nameOfTypeFromValue_WithGivenType_ShouldWork() {
  QCOMPARE(Utils::nameOfTypeFromValue(integer()), "int");
  QCOMPARE(Utils::nameOfTypeFromValue(real()), "double");

  QCOMPARE(Utils::nameOfTypeFromValue(Struct1()), "TestUtils::Struct1");

  QCOMPARE(Utils::nameOfTypeFromValue(QString()), "QString");

  QCOMPARE((Utils::nameOfTypeFromValue(std::pair<int, int>())),
           "std::pair<int, int>");
  QCOMPARE((Utils::nameOfTypeFromValue(pair<int, int>())),
           "std::pair<int, int>");
}

QTEST_MAIN(TestUtils)
