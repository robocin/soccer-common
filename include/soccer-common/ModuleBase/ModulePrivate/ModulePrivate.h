#ifndef SOCCER_COMMON_MODULEPRIVATE_H
#define SOCCER_COMMON_MODULEPRIVATE_H

#include <QTimer>
#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include "soccer-common/Parameters/Parameters.h"

class ModulePrivate : public QObject, private QRunnable {
  Q_OBJECT

 public:
  explicit ModulePrivate(QThreadPool* threadPool);

 public slots:
  void runInParallel();
  void prepareToDelete();

 protected:
  Parameters::Handler parametersHandler;
  SharedWrapper<Parameters::UpdateRequests, std::mutex> updateRequests;

  virtual void update();
  virtual void exec() = 0;

 private:
  volatile std::atomic<QThreadPool*> threadPool;
  std::mutex execMutex;

  void parametersUpdate();
  void run() final;

  static void waitOrDelete(ModulePrivate* object);
};

#endif // SOCCER_COMMON_MODULEPRIVATE_H
