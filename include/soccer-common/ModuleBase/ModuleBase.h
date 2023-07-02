#ifndef SOCCER_COMMON_MODULEBASE_H
#define SOCCER_COMMON_MODULEBASE_H

#include <QObject>
#include "ModulePrivate/ModulePrivate.h"
#include "soccer-common/Gui/GameVisualizer/GameVisualizerBase/GameVisualizerBase.h"

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

  void onInit(const Modules* modules);
  void onBuildParameters(Parameters::Handler& parameters);
  void onConnectModules(const Modules* modules);

  void sendParameters(const QJsonObject& parameters);

  /* interface */ signals:
  void setInterfaceScoreboard(int first, int second);
  void setInterfaceTeamColor(const QColor& firstColor, const QColor& secondColor);
  void setInterfaceAttackSide(bool isRight);
  void setInterfaceRefereeCommand(const QString& command);

 protected:
  virtual void buildParameters(Parameters::Handler& parameters);
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

// -------------------------------------------------------------------------- //

class ModuleExtension {
 public:
  template <class M>
  explicit ModuleExtension(const QString& group, M* m) {
    static_assert(std::is_base_of_v<ModuleBase, M>, "M must be a ModuleBase type.");
    QObject::connect(
        m,
        &ModuleBase::onBuildParameters,
        m,
        [this, g = group](Parameters::Handler& parameters) {
          Parameters::Handler handler;
          extendedBuildParameters(handler);
          if (!handler.empty()) {
            parameters[g] = std::move(handler);
          }
        },
        Qt::DirectConnection);
    QObject::connect(
        m,
        &ModuleBase::onConnectModules,
        m,
        [this](const Modules* modules) {
          extendedConnectModules(modules);
        },
        Qt::DirectConnection);
    QObject::connect(
        m,
        &ModuleBase::onInit,
        m,
        [this](const Modules* modules) {
          extendedInit(modules);
        },
        Qt::DirectConnection);
  }
  template <class E, class M, std::enable_if_t<std::is_base_of_v<ModuleExtension, E>, bool> = true>
  inline ModuleExtension([[maybe_unused]] E* extension, M* m) :
      ModuleExtension(Utils::nameOfType<E>(), m) {
  }
  virtual ~ModuleExtension() = default;
  virtual void extendedBuildParameters(Parameters::Handler&);
  virtual void extendedConnectModules(const Modules*);
  virtual void extendedInit(const Modules*);
};

#endif // SOCCER_COMMON_MODULEBASE_H
