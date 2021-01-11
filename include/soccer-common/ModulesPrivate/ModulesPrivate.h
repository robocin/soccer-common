#ifndef MODULESPRIVATE_H
#define MODULESPRIVATE_H

#include "soccer-common/gui/gui.h"
#include "soccer-common/ModuleBase/ModuleBase.h"

class ModulesPrivate : public QObject {
  Q_OBJECT

  class Timers {
    QObject* m_parent;
    mutable QMap<int, QTimer*> m_map;

    template <std::size_t I>
    inline QTimer* get() const {
      if (!m_map.contains(I)) {
        QTimer* timer = new QTimer(m_parent);
        timer->start(I);
        m_map[I] = timer;
      }
      return m_map[I];
    }

   public:
    explicit Timers(QObject* parent) : m_parent(parent) {
    }

    ~Timers() {
      clear();
    }

    inline void clear() {
      for (auto it = m_map.begin(); it != m_map.end(); ++it) {
        it.value()->deleteLater();
      }
      m_map.clear();
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
  std::unique_ptr<Timers> m_timers;

 public:
  ModulesPrivate(MainWindow* gui);

  MainWindow* gui() const;
  Timers* timers() const;

 signals:
  void setup();
  void impulse();

  void rebuild();

 public slots:
  void onPlayPauseButtonPressed(bool isRunning);

 protected:
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

    static void deleteIfExists(T* instance) {
      if (instance) {
        qWarning().nospace()
            << "scheduling the deletion of " << instance << ".";
        static_cast<QObject*>(instance)->deleteLater();
      }
    }

    static void setup(T* instance, M* modules) {
      qWarning() << "performing" << instance << "setup.";
      static_cast<ModuleBase*>(instance)->setup(modules);
    }

    /* connecting updates, (TODO: painting) and building dialog before object
     * build. Trazer pra dentro da classe, se possível.
     */
    inline static void
    setDefaultConnections(T* ref, ModuleBox* moduleBox, MainWindow* gui) {
      QObject::connect(ref,
                       &ModuleBase::sendParameters,
                       moduleBox->dialog(),
                       &ParametersDialog::build);

      QObject::connect(moduleBox->dialog(),
                       &ParametersDialog::onChangingParameters,
                       ref,
                       &ModuleBase::receiveUpdateRequests);

      QObject::connect(ref,
                       &ModuleBase::draw,
                       gui->gameVisualizer(),
                       &GameVisualizer::draw);
    }

    static void build(T*& ref,
                      const F& factory,
                      M* modules,
                      ModuleBox* moduleBox,
                      Args... args) {
      qWarning().nospace() << "building " << Utils::nameOfType<T>() << ".";

      deleteIfExists(ref);

      QString type = moduleBox->currentText();
      ref = factory[type](args...);

      qWarning().nospace() << "a new instance of " << Utils::nameOfType<T>()
                           << " with type " << type << " was created: " << ref
                           << ".";

      setDefaultConnections(ref,
                            moduleBox,
                            static_cast<ModulesPrivate*>(modules)->gui());

      static_cast<ModuleBase*>(ref)->build();

      QObject::connect(modules,
                       &ModulesPrivate::setup,
                       ref,
                       std::bind(Maker::setup, ref, modules));

      QObject::connect(modules,
                       &ModulesPrivate::impulse,
                       ref,
                       &ModuleBase::runInParallel);
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
  void clear();
};

#endif // MODULESPRIVATE_H
