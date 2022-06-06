#include <QtTest>

#include "soccer-common/Field/Field.h"

class TestField : public QObject {
  Q_OBJECT

 public:
  TestField();
  ~TestField();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void test_field_constexpr_withVSS3x3Values();
};
