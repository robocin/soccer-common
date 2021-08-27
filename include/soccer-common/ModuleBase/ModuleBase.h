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
  friend class ModulesPrivate;
  Q_OBJECT

 public:
  explicit ModuleBase(QThreadPool* threadPool);
  ~ModuleBase() override = default;

 signals:
  void onReceiveUpdateRequests();
  void sendParameters(const QJsonObject& parameters);

  /* interface */ signals:
  void setInterfaceScoreboard(int first, int second);
  void setInterfaceTeamColor(const QColor& firstColor, const QColor& secondColor);
  void setInterfaceAttackSide(bool isRight);

 protected:
  Parameters::Handler& parameters();

  virtual void buildParameters();
  virtual void connectModules(const Modules* modules);

 protected slots:
  virtual void init(const Modules* modules);

 private:
  using ModulePrivate::parametersHandler;
  using ModulePrivate::updateRequests;

 private slots:
  void build();
  void setup(const Modules* modules);
  void receiveUpdateRequests(const Parameters::UpdateRequests& updates);
};

// -------------------------------------------------------------------------- //

class IndexedModuleBase : public ModuleBase {
  Q_OBJECT

 public:
  explicit IndexedModuleBase(int index, QThreadPool* threadPool);
  ~IndexedModuleBase() override = default;

  int index() const;

 private:
  int m_index;
};

#endif // SOCCER_COMMON_MODULEBASE_H
