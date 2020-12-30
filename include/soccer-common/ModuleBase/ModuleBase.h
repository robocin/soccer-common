#ifndef MODULEBASE_H
#define MODULEBASE_H

#include <QObject>
#include "ModulePrivate/ModulePrivate.h"

class Modules;

class ModuleBase : public ModulePrivate {
  Q_OBJECT

 public:
  ModuleBase();
  ~ModuleBase() override;

  void build(QThreadPool* threadPool);
  void setup(const Modules* modules);

 signals:
  void sendParameters(const QJsonObject& parameters);
  /* TODO: (requires: ModulesPrivate, Gui))
    void sendPainting(int uniqueIntegerKey,
                      Painting* painting,
                      Painting::Layers layer = Painting::Layers::Middle);
  */
 public slots:
  virtual void
  receiveUpdateRequests(const Parameters::UpdateRequests& updates) = 0;

 protected:
  virtual void buildParameters();

  virtual void connectModules(const Modules* modules);
  virtual void init(const Modules* modules);
};

class IndexedModuleBase : public ModuleBase {
  Q_OBJECT

 public:
  explicit IndexedModuleBase();
  ~IndexedModuleBase() override;

  void build(int index, QThreadPool* threadPool);

 protected:
  using ModuleBase::build;

  int index() const;

 private:
  int m_index;
};

#endif // MODULEBASE_H
