#include <QtTest>

#include "soccer-common/Parameters/Parameters.h"

class TestParameters : public QObject {
  Q_OBJECT

  struct Args {
    int maxSpeed = 0;
    long long maxVelocity = 130;
    QPoint startPosition = QPoint(50, 50);
    QString robotName = "wall-e";
    double epsilon = 1.0;

    struct Draw {
      bool canDraw = false;
      QString colorName = "blue";
    };
    Draw draw;

    enum class MyEnum { A, B, C };
    MyEnum myEnum = MyEnum::A;
  } args;

  Parameters::Handler handler;

 public:
  TestParameters();
  ~TestParameters();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void test_Slider_WithValidParameters_ShouldConstruct();
  void test_Slider_WithRefOutOfRange_ShouldThrowException();
};
