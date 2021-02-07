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

void TestUtils::test_nameOfType_WithGivenTypeFromValue_ShouldWork() {
  QCOMPARE(Utils::nameOfType(integer()), "int");
  QCOMPARE(Utils::nameOfType(real()), "double");

  QCOMPARE(Utils::nameOfType(Struct1()), "TestUtils::Struct1");

  QCOMPARE(Utils::nameOfType(QString()), "QString");

  QCOMPARE((Utils::nameOfType(std::pair<int, int>())), "std::pair<int, int>");
  QCOMPARE((Utils::nameOfType(pair<int, int>())), "std::pair<int, int>");

  integer intRef{};
  QCOMPARE(Utils::nameOfType(intRef), "int&");

  integer* intPtr{};
  QCOMPARE(Utils::nameOfType(intPtr), "int*&");

  const QString cstrRef{};
  QCOMPARE(Utils::nameOfType(cstrRef), "const QString&");

  const QString* cstrPtr{};
  QCOMPARE(Utils::nameOfType(cstrPtr), "const QString*&");
}

QTEST_MAIN(TestUtils)
