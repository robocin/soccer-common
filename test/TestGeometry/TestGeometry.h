#include <QtTest>

#include "Geometry/Geometry.h"

class TestGeometry : public QObject {
  Q_OBJECT

 public:
  TestGeometry();
  ~TestGeometry();

 private slots:
  void initTestCase();

  void init();

  void cleanup();

  void cleanupTestCase();

  void testDistance();
};
