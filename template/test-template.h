#include <QtTest>

// add necessary includes here

class $$NameOfTest : public QObject {
  Q_OBJECT

 public:
  $$NameOfTest();
  ~$$NameOfTest();

 private slots:
  // called before the first test function
  void initTestCase();

  // called before every test function
  void init();

  // called after every test function
  void cleanup();

  // called after the last test function
  void cleanupTestCase();

  void test$$NameOfClassOrMethod$$1();
  void test$$NameOfClassOrMethod$$2();
  void test$$NameOfClassOrMethod$$3();
  // ...
  void test$$NameOfClassOrMethod$$N();
};
