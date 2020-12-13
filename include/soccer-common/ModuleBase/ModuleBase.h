#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <QObject>
#include "ModulePrivate/ModulePrivate.h"

class Modules;

class ModuleBase : public ModulePrivate {
  Q_OBJECT

 public:
  explicit ModuleBase(QThreadPool* threadPool);
  ~ModuleBase() override;

  void setup(const Modules* modules) {
    connectModules(modules);
    buildParameters();
    init(modules);
  }

 protected:
  virtual void connectModules(const Modules* modules);
  virtual void buildParameters();
  virtual void init(const Modules* modules);
};

class IndexedModuleBase : public ModuleBase {
  Q_OBJECT

 public:
  explicit IndexedModuleBase(int index, QThreadPool* threadPool);
  ~IndexedModuleBase() override;

 protected:
  int index() const;

 private:
  int m_index;
};

#endif // MODULEBASE_H
