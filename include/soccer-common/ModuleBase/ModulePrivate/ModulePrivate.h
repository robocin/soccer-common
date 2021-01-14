#ifndef MODULEPRIVATE_H
#define MODULEPRIVATE_H

#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <boost/lockfree/spsc_queue.hpp>
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
  boost::lockfree::spsc_queue<Parameters::UpdateRequests,
                              boost::lockfree::capacity<16>>
      spscUpdateRequests;

  virtual void update();
  virtual void exec() = 0;
  virtual void wasSkipped();

 private:
  QThreadPool* threadPool;
  QMutex execMutex;

  void parametersUpdate();
  void run() override final;
};

#endif // MODULEPRIVATE_H
