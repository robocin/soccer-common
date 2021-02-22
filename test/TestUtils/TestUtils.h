#include <QtTest>

#include "soccer-common/Utils/Utils.h"

class TestUtils : public QObject {
  Q_OBJECT

  struct Struct1 {};
  using integer = int;
  typedef double real;
  template <class U, class V>
  using pair = std::pair<U, V>;

 public:
  TestUtils();
  ~TestUtils();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void test_nameOfType_WithGivenType_ShouldWork();
  void test_nameOfTypes_WithGivenTypes_ShouldWork();

  void test_nameOfType_WithGivenTypeFromValue_ShouldWork();
  void test_nameOfTypes_WithGivenTypesFromValues_ShouldWork();
};
