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

void TestUtils::test_nameOfTypes_WithGivenTypes_ShouldWork() {
  {
    QString nameOfTypes = Utils::nameOfTypes<int, double, char, QString>();
    QCOMPARE(nameOfTypes, "[int, double, char, QString]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes<>();
    QCOMPARE(nameOfTypes, "[]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes<integer>();
    QCOMPARE(nameOfTypes, "[int]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes<const real>();
    QCOMPARE(nameOfTypes, "[const double]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes<QString*>();
    QCOMPARE(nameOfTypes, "[QString*]");
  }
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

void TestUtils::test_nameOfTypes_WithGivenTypesFromValues_ShouldWork() {
  {
    QString nameOfTypes =
        Utils::nameOfTypes(integer(), real(), char(), QString());
    QCOMPARE(nameOfTypes, "[int, double, char, QString]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes();
    QCOMPARE(nameOfTypes, "[]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes(integer());
    QCOMPARE(nameOfTypes, "[int]");
  }
  {
    const real& value = 0.0;
    QString nameOfTypes = Utils::nameOfTypes(value);
    QCOMPARE(nameOfTypes, "[const double&]");
  }
  {
    QString nameOfTypes = Utils::nameOfTypes((QString*) (nullptr));
    QCOMPARE(nameOfTypes, "[QString*]");
  }
}

QTEST_MAIN(TestUtils)
