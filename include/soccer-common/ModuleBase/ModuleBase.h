#ifndef SOCCER_COMMON_MODULEBASE_H
#define SOCCER_COMMON_MODULEBASE_H

#include <QObject>
#include "ModulePrivate/ModulePrivate.h"
#include "soccer-common/Gui/GameVisualizer/GameVisualizer.h"

/*!
 * \brief It will be defined in the executable project.
 */
class Modules;

class ModuleBase : public ModulePrivate {
  Q_OBJECT

 public:
  explicit ModuleBase(QThreadPool* threadPool);
  ~ModuleBase() override = default;

  void build();
  void setup(const Modules* modules);

 signals:
  void sendParameters(const QJsonObject& parameters);

 public slots:
  void receiveUpdateRequests(const Parameters::UpdateRequests& updates);

 protected:
  Parameters::Handler& parameters();
  virtual void buildParameters();

  virtual void connectModules(const Modules* modules);
  virtual void init(const Modules* modules);

 private:
  using ModulePrivate::parametersHandler;
  using ModulePrivate::updateRequests;
};

// -------------------------------------------------------------------------- //

class IndexedModuleBase : public ModuleBase {
  Q_OBJECT

 public:
  explicit IndexedModuleBase(int index, QThreadPool* threadPool);
  ~IndexedModuleBase() override = default;

 protected:
  int index() const;

 private:
  int m_index;
};

#endif // SOCCER_COMMON_MODULEBASE_H
