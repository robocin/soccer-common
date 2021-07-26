#include <QtTest>

#include "soccer-common/Parameters/Parameters.h"

class TestParameters : public QObject {
  Q_OBJECT

  struct Args {
    enum class MyEnum : int { A, B, C };
  };

 public:
  TestParameters();
  ~TestParameters();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  // types:
  void test_ParameterType_eval_WithInvalidParameters_ShouldReturnNullopt();
  void test_ParameterType_eval_WithValidParameters_ShouldWork();

  void test_Text_WithValidParameters_ShouldConstruct();
  void test_Text_WithInvalidParameters_ShouldThrowException();

  void test_SpinBox_WithValidParameters_ShouldConstruct();
  void test_SpinBox_WithInvalidParameters_ShouldThrowException();

  void test_DoubleSpinBox_WithValidParameters_ShouldConstruct();
  void test_DoubleSpinBox_WithInvalidParameters_ShouldThrowException();

  void test_MappedAngleInRadiansToDegrees_WithValidParameters_ShouldConstruct();
  void test_MappedAngleInRadiansToDegrees_WithInvalidParameters_ShouldThrowException();

  void test_Slider_WithValidParameters_ShouldConstruct();
  void test_Slider_WithInvalidParameters_ShouldThrowException();

  void test_CheckBox_WithValidParameters_ShouldConstruct();

  void test_ComboBox_WithValidParameters_ShouldConstruct();
  void test_ComboBox_WithInvalidParameters_ShouldThrowException();

  void test_MappedComboBox_WithValidParameters_ShouldConstruct();
  void test_MappedComboBox_WithInvalidParameters_ShouldThrowException();

  void test_PushButton_WithValidParameters_ShouldConstruct();
  void test_PushButton_WithInvalidParameters_ShouldThrowException();

  // handler:
  void test_ParametersHandler_WithValidParametersShouldConstruct();
};
