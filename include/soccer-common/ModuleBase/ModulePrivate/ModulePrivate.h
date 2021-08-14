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

  static void waitOrDelete(ModulePrivate* object);

 public slots:
  void prepareToDelete();

 protected:
  Parameters::Handler parametersHandler;
  SharedWrapper<Parameters::UpdateRequests, std::mutex> updateRequests;

  virtual void update();
  virtual void exec() = 0;

 private:
  volatile std::atomic<QThreadPool*> threadPool;
  std::mutex execMutex;

  QVector<Parameters::ParameterBase*> parametersUpdate();
  void run() final;

 signals:
  void runInParallel();

 protected slots:
  void tryStart();

 private:
  struct ParametersUpdateGuard {
    QVector<Parameters::ParameterBase*> parameters;

    inline explicit ParametersUpdateGuard(QVector<Parameters::ParameterBase*>&& parameters) :
        parameters(parameters) {
      for (auto parameter : parameters) {
        parameter->setUpdated(true);
      }
    }

    inline ~ParametersUpdateGuard() {
      for (auto parameter : parameters) {
        parameter->setUpdated(false);
      }
    }
  };
};

#endif // SOCCER_COMMON_MODULEPRIVATE_H
