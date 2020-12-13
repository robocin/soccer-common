#ifndef MODULEPRIVATE_H
#define MODULEPRIVATE_H

#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include "soccer-common/Parameters/Parameters.h"

class ModulePrivate : public QObject, private QRunnable {
  Q_OBJECT
 public:
  explicit ModulePrivate(QThreadPool* threadPool);
  ~ModulePrivate() override;

 public slots:
  void runInParallel();

 protected:
  Parameters::ParametersHandler& parameters();

  virtual void wasSkipped();
  virtual void exec() = 0;

 private:
  Parameters::ParametersHandler parametersHandler;
  QThreadPool* threadPool;
  QMutex execMutex;

  void run() override final;
};

#endif // MODULEPRIVATE_H
