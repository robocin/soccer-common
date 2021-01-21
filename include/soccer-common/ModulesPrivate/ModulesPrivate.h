#ifndef MODULESPRIVATE_H
#define MODULESPRIVATE_H

#include "soccer-common/gui/gui.h"
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
        QTimer* timer = new QTimer();
        timer->start(I);
        timer->moveToThread(m_thread);
        m_map[I] = timer;
      }
      return m_map[I];
    }

    inline void clear() {
      for (auto t : m_map) {
        QMetaObject::invokeMethod(t, &QTimer::stop, Qt::QueuedConnection);
        QMetaObject::invokeMethod(t,
                                  &QTimer::deleteLater,
                                  Qt::QueuedConnection);
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

    inline QTimer* asap() const {
      return get<0>();
    }
  };

  MainWindow* m_gui;

  QThread* m_modulesThread;

  Timers m_timers;

 public:
  explicit ModulesPrivate(MainWindow* gui);
  ~ModulesPrivate();

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

  template <class T, class M, class... Args>
  class Maker {
    static_assert(std::is_base_of_v<ModuleBase, T>);

    static_assert(std::is_same_v<Modules, M>);
    static_assert(std::is_base_of_v<ModulesPrivate, M>);

    using F = typename InheritanceFactorySafeMap<T, Args...>::type;

    M* modules;

    T*& ref;
    std::optional<int> index; // can be indexed, or not.

    F factory;

    static void
    disconnectAndDelete(ModuleBase* ref,
                        QVector<QMetaObject::Connection> connections) {
      for (QMetaObject::Connection connection : connections) {
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

        connections += QObject::connect(modules,
                                        &ModulesPrivate::impulse,
                                        ref,
                                        &ModuleBase::runInParallel);
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
      return connections;
    }

    static void build(T*& ref,
                      const F& factory,
                      M* modules,
                      ModuleBox* moduleBox,
                      Args... args) {
      qWarning().nospace() << "building " << Utils::nameOfType<T>() << ".";

      QString type = moduleBox->currentText();
      ref = factory[type](args...);
      static_cast<QObject*>(ref)->moveToThread(
          static_cast<ModulesPrivate*>(modules)->modulesThread());

      qWarning().nospace() << "a new instance of " << Utils::nameOfType<T>()
                           << " with type " << type << " was created: " << ref
                           << ".";

      auto connections = setDefaultConnections(ref, modules, moduleBox);
      QObject::connect(modules,
                       &ModulesPrivate::prepareToDelete,
                       ref,
                       std::bind(Maker::disconnectAndDelete, ref, connections));

      static_cast<ModuleBase*>(ref)->build();
    }

    static void
    setToolTip(const F& factory, const QString& type, ModuleBox* moduleBox) {
      QStringList description;
      description += "• Type: " + type + ";";
      QString info = factory[type].description();
      if (!info.isEmpty()) {
        description += "• Description: " + info + ";";
      }
      moduleBox->setToolTip(description.join('\n'));
    }

    static void make(T*& ref,
                     const F& factory,
                     M* modules,
                     ModuleBox* moduleBox,
                     Args... args) {
      QString type = moduleBox->currentText();

      build(ref, factory, modules, moduleBox, args...);
      setToolTip(factory, type, moduleBox);
    }

    static ModuleBox* getModuleBox(MainWindow* gui,
                                   const std::optional<int>& index) {
      if (index) {
        return gui->indexedModuleBox(*index, Utils::nameOfType<T>());
      } else {
        return gui->moduleBox(Utils::nameOfType<T>());
      }
    }

    template <class... Types>
    inline void exec(Types&&... types) {
      if (factory.empty()) {
        qWarning() << "factory of" << Utils::nameOfType<T>() << "is empty.";
        return;
      }
      qWarning().nospace() << "making " << Utils::nameOfType<T>() << "...";
      MainWindow* gui = static_cast<ModulesPrivate*>(modules)->gui();
      //
      ModuleBox* moduleBox = getModuleBox(gui, index);
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
    Maker(M* t_modules,
          T*& t_ref,
          const InheritanceFactorySafeMap<T, Args...>& t_factory) :
        modules(t_modules),
        ref(t_ref),
        factory(t_factory) {
    }

    template <class R = void, class... Types>
    std::enable_if_t<!std::is_base_of_v<IndexedModuleBase, T>, R> // !indexed
    operator()(Types&&... types) {
      exec(std::forward<Types>(types)...);
    }

    template <class R = void, class... Types>
    std::enable_if_t<std::is_base_of_v<IndexedModuleBase, T>, R> // indexed
    operator()(int moduleIndex, Types&&... types) {
      index.emplace(moduleIndex);
      exec(moduleIndex, std::forward<Types>(types)...);
    }
  };

 private:
  void prepareToDeleteAndDisconnect();
};

#endif // MODULESPRIVATE_H
