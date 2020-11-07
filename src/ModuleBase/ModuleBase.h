#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <QObject>
#include "AnyVisitor.h"
#include "ModulePrivate.h"

class ModuleBase : public ModulePrivate {
  Q_OBJECT
  using ModulePrivate::visitor;

 public:
  explicit ModuleBase(QThreadPool* threadPool);
  ~ModuleBase() override;

 protected:
  template <class T, class F>
  void insertReceiveFunction(const F& f) {
    visitor->insert<T>(f);
  }

  void exec() override = 0;
  void insertReceivers() override = 0;
  void buildParameters() override = 0;
};

#endif // MODULEBASE_H