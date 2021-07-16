#ifndef SOCCER_COMMON_MODULESPRIVATE_H
#define SOCCER_COMMON_MODULESPRIVATE_H

#include "soccer-common/Gui/Gui.h"
#include "soccer-common/ModuleBase/ModuleBase.h"

class ModulesPrivate : public QObject {
  Q_OBJECT

  class Timers {
    friend class ModulesPrivate;

    QThread* m_thread;
    mutable QMap<int, QTimer*> m_map;

    template <std::size_t I>
    inline QTimer* get() const {
      if (!m_map.contains(I)) {
        auto* timer = new QTimer();
        timer->setTimerType(Qt::PreciseTimer);
        timer->start(I);
        timer->moveToThread(m_thread);
        m_map[I] = timer;
      }
      return m_map[I];
    }

    inline void clear() {
      for (auto t : m_map) {
        QMetaObject::invokeMethod(t, &QTimer::stop, Qt::QueuedConnection);
      }
      for (auto t : m_map) {
        QMetaObject::invokeMethod(t, &QTimer::deleteLater, Qt::QueuedConnection);
      }
      m_map.clear();
    }

   public:
    explicit Timers(QThread* thread) : m_thread(thread) {
    }

    ~Timers() {
      clear();
    }

    template <std::size_t I>
    inline QTimer* hertz() const {
      static_assert(0 < I && I <= 600, "out of range.");
      return get<1000 / I>();
    }

    [[maybe_unused]] inline QTimer* asap() const {
      return get<0>();
    }
  };

  MainWindow* m_gui;

  QThread* m_modulesThread;

  Timers m_timers;

 public:
  explicit ModulesPrivate(MainWindow* gui);
  ~ModulesPrivate() override = default;

  MainWindow* gui() const;
  Timers* timers() const;

 signals:
  void setup();
  void impulse();

  void prepareToDelete();
  void rebuild();

 public slots:
  void onPlayPauseButtonPressed(bool isRunning);

 protected:
  QThread* modulesThread() const;

 private:
  template <class M, class T, class... Args>
  class Maker {
    static_assert(std::is_base_of_v<ModuleBase, T>);

    static_assert(std::is_same_v<Modules, M>);
    static_assert(std::is_base_of_v<ModulesPrivate, M>);

    using F = typename InheritanceFactorySafeMap<T, Args...>::type;

    M* modules;
    T*& ref;
    F factory;

    static void disconnectAndDelete(ModuleBase* ref,
                                    const QVector<QMetaObject::Connection>& connections) {
      for (const QMetaObject::Connection& connection : connections) {
        QObject::disconnect(connection);
      }
      ref->prepareToDelete();
    }

    static void setup(T* instance, M* modules) {
      qWarning() << "performing" << instance << "setup.";
      static_cast<ModuleBase*>(instance)->setup(modules);
    }

    inline static QVector<QMetaObject::Connection>
    setDefaultConnections(T* ref, M* modules, ModuleBox* moduleBox) {
      QVector<QMetaObject::Connection> connections;
      /* ModulesPrivate */ {
        connections += QObject::connect(modules,
                                        &ModulesPrivate::setup,
                                        ref,
                                        std::bind(Maker::setup, ref, modules));

        connections +=
            QObject::connect(modules, &ModulesPrivate::impulse, ref, &ModuleBase::runInParallel);
      }
      /* ModuleBox */ {
        connections += QObject::connect(ref,
                                        &ModuleBase::sendParameters,
                                        moduleBox->dialog(),
                                        &ParametersDialog::build);

        connections += QObject::connect(moduleBox->dialog(),
                                        &ParametersDialog::onChangingParameters,
                                        ref,
                                        &ModuleBase::receiveUpdateRequests);
      }
      /* interface */ {
        auto gui = static_cast<ModulesPrivate*>(modules)->gui();
        connect(ref,
                &ModuleBase::setInterfaceScoreboard,
                gui->scoreboard(),
                &ScoreboardWidget::setScore);

        connect(ref,
                &ModuleBase::setInterfaceTeamColor,
                gui->scoreboard(),
                &ScoreboardWidget::setColor);

        connect(ref,
                &ModuleBase::setInterfaceTeamColor,
                gui->colorTeam(),
                &ColorTeamWidget::setColor);

        connect(ref, &ModuleBase::setInterfaceTeamColor, gui, [gui](const QColor& color) {
          gui->setRobotDetailsColor(color);
        });

        connect(ref,
                &ModuleBase::setInterfaceAttackSide,
                gui->attackSide(),
                &AttackSideWidget::setRightSide);
      }
      return connections;
    }

    static void build(T*& ref, const F& factory, M* modules, ModuleBox* moduleBox, Args... args) {
      qWarning().nospace() << "building " << Utils::nameOfType<T>() << ".";

      if (auto oldRef = ref) {
        ModuleBase::waitOrDelete(oldRef);
      }

      QString type = moduleBox->currentText();
      ref = factory[type](args...);
      static_cast<QObject*>(ref)->moveToThread(
          static_cast<ModulesPrivate*>(modules)->modulesThread());

      QString detail;
      if constexpr (std::is_base_of_v<IndexedModuleBase, T>) {
        int index = static_cast<IndexedModuleBase*>(ref)->index();
        detail += QString(" (index '%1')").arg(index);
      }

      qWarning().nospace().noquote()
          << "a new instance of " << Utils::nameOfType<T>() << detail << " with type "
          << "\"" << type << "\""
          << " was created: " << ref << ".";

      auto connections = setDefaultConnections(ref, modules, moduleBox);
      QObject::connect(modules,
                       &ModulesPrivate::prepareToDelete,
                       ref,
                       std::bind(Maker::disconnectAndDelete, ref, connections));

      static_cast<ModuleBase*>(ref)->build();
    }

    static void setToolTip(const F& factory, const QString& type, ModuleBox* moduleBox) {
      QStringList description;
      description += "• Type: " + type + ";";
      QString info = factory[type].description();
      if (!info.isEmpty()) {
        description += "• Description: " + info + ";";
      }
      moduleBox->setToolTip(description.join('\n'));
    }

    static void make(T*& ref, const F& factory, M* modules, ModuleBox* moduleBox, Args... args) {
      QString type = moduleBox->currentText();
      setToolTip(factory, type, moduleBox);
      build(ref, factory, modules, moduleBox, args...);
    }

    template <class... Types>
    [[maybe_unused]] static ModuleBox* getModuleBox(MainWindow* gui, Types&&...) {
      return gui->moduleBox(Utils::nameOfType<T>());
    }

    template <class... Types>
    [[maybe_unused]] static ModuleBox* getModuleBox(MainWindow* gui, int index, Types&&...) {
      return gui->indexedModuleBox(index, Utils::nameOfType<T>());
    }

    template <class... Types>
    inline void exec(Types&&... types) {
      MainWindow* gui = static_cast<ModulesPrivate*>(modules)->gui();
      //
      ModuleBox* moduleBox = getModuleBox(gui, std::forward<Types>(types)...);
      //
      QObject::connect(moduleBox,
                       &ModuleBox::onCurrentTextChanged,
                       modules,
                       std::bind(Maker::make,
                                 std::ref(ref),
                                 factory,
                                 modules,
                                 moduleBox,
                                 std::forward<Types>(types)...));
      //
      QObject::connect(modules,
                       &ModulesPrivate::rebuild,
                       modules,
                       std::bind(Maker::build,
                                 std::ref(ref),
                                 factory,
                                 modules,
                                 moduleBox,
                                 std::forward<Types>(types)...));
      //
      moduleBox->setComboBoxItems(factory.keys());
    }

   public:
    Maker(M* t_modules, T*& t_ref, const InheritanceFactorySafeMap<T, Args...>& t_factory) :
        modules(t_modules),
        ref(t_ref),
        factory(t_factory) {
    }

    template <class... Types>
    void operator()(Types&&... types) {
      if (factory.empty()) {
        qWarning() << "factory of" << Utils::nameOfType<T>() << "is empty.";
        return;
      }
      qWarning().nospace() << "making " << Utils::nameOfType<T>() << "...";
      exec(std::forward<Types>(types)...);
    }
  };

 protected:
  template <class M, class T, class F, class... Types>
  void makeModule(M* modules, T*& ref, const F& factory, Types&&... types) {
    Q_ASSERT(ref == nullptr);
    Maker(modules, ref, factory)(std::forward<Types>(types)...);
  }

  template <class M, class T, class F, class... Types>
  void makeModule(M* modules, QVector<T*>& vect, const F& factory, Types&&... types) {
    Q_ASSERT(vect.empty());
    int n = static_cast<ModulesPrivate*>(modules)->gui()->maxRobots();
    vect.resize(n);
    for (int i = 0; i < n; ++i) {
      Maker(modules, vect[i], factory)(i, std::forward<Types>(types)...);
    }
  }

 private:
  void prepareToDeleteAndDisconnect();
};

#endif // SOCCER_COMMON_MODULESPRIVATE_H
