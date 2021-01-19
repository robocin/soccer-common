#ifndef MODULEPRIVATE_H
#define MODULEPRIVATE_H

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
  Parameters::Handler parametersHandler;
  SharedWrapper<Parameters::UpdateRequests, std::mutex> updateRequests;

  virtual void update();
  virtual void exec() = 0;
  virtual void wasSkipped();

 private:
  QThreadPool* threadPool;
  std::mutex execMutex;

  void parametersUpdate();
  void run() override final;
};

#endif // MODULEPRIVATE_H
