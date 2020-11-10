#ifndef MODULEPRIVATE_H
#define MODULEPRIVATE_H

#include <any>
#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QThreadPool>

class ModulePrivate : public QObject, private QRunnable {
  Q_OBJECT
  class AnyVisitor;

 public:
  explicit ModulePrivate(QThreadPool* threadPool);
  ~ModulePrivate() override;

 public slots:
  void receive(const std::any& package) const;
  void runInParallel();
  void receiveAndRunInParallel(const std::any& package);

 protected:
  std::unique_ptr<AnyVisitor> visitor;

  virtual void exec() = 0;
  virtual void insertReceivers() = 0;
  virtual void buildParameters() = 0;

 private:
  QThreadPool* threadPool;
  QMutex execMutex;

  void run() override final;
};

#endif // MODULEPRIVATE_H
