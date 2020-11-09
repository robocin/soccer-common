#include "TestParameters.h"

TestParameters::TestParameters() {
}

TestParameters::~TestParameters() {
}

void TestParameters::initTestCase() {
}

void TestParameters::init() {
}

void TestParameters::cleanup() {
}

void TestParameters::cleanupTestCase() {
}

void TestParameters::test_Slider_WithValidParameters_ShouldConstruct() {
  int x = 50;
  auto slider = Parameters::Slider(x, 0, 100, "robocin 2020.");
  QCOMPARE(slider.inputType(), Parameters::InputType::Slider);
  QCOMPARE(slider.description(), "robocin 2020.");
  QCOMPARE(slider.isChooseable(), false);
  QCOMPARE(slider.type(), Utils::nameOfTypeFromValue(x));
}

void TestParameters::test_Slider_WithRefOutOfRange_ShouldThrowException() {
  long long y = 110;
  bool error = false;
  try {
    auto slider = Parameters::Slider(y, 0ll, 100ll);
  } catch (...) {
    error = true;
  }
  QVERIFY(error);
}

QTEST_MAIN(TestParameters)
