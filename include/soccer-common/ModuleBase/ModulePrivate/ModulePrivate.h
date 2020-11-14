#ifndef MODULEPRIVATE_H
#define MODULEPRIVATE_H

#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include "soccer-common/Package/Package.h"
#include "soccer-common/Parameters/Parameters.h"

class ModulePrivate : public QObject, private QRunnable {
  Q_OBJECT
  class AnyVisitor;

 public:
  explicit ModulePrivate(QThreadPool* threadPool);
  ~ModulePrivate() override;

 public slots:
  void receive(const Package& package);
  void runInParallel();
  void receiveAndRunInParallel(const Package& package);

 protected:
  std::unique_ptr<AnyVisitor> visitor;
  Parameters::ParametersHandler& parameters();

  virtual void wasNotReceived(const Package& package);
  virtual void wasSkipped();

  virtual void exec() = 0;
  virtual void buildParameters() = 0;
  virtual void insertReceivers() = 0;

 private:
  Parameters::ParametersHandler parametersHandler;
  QThreadPool* threadPool;
  QMutex execMutex;

  void run() override final;
};

#endif // MODULEPRIVATE_H
