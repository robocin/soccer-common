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

  virtual void connectModules(const Modules* modules) = 0;

 protected:
  void exec() override = 0;
  void buildParameters() override = 0;
};

class IndexedModuleBase : public ModuleBase {
  Q_OBJECT

 public:
  explicit IndexedModuleBase(int index, QThreadPool* threadPool);
  ~IndexedModuleBase() override;

  void connectModules(const Modules* modules) override = 0;

 protected:
  int index() const;

  void exec() override = 0;
  void buildParameters() override = 0;

 private:
  int m_index;
};

#endif // MODULEBASE_H
