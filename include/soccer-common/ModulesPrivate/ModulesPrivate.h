#ifndef MODULESPRIVATE_H
#define MODULESPRIVATE_H

#include "soccer-common/gui/gui.h"
#include "soccer-common/ModuleBase/ModuleBase.h"

// remains to add IndexedModules

class ModulesPrivate : public QObject {
  Q_OBJECT

  class Timers {
    QObject* m_parent;
    mutable QMap<int, QTimer*> m_map;

   public:
    explicit Timers(QObject* parent = nullptr) : m_parent(parent) {
    }

    ~Timers() {
      clear();
    }

    void clear() {
      for (auto it = m_map.begin(); it != m_map.end(); ++it) {
        it.value()->deleteLater();
        it.value() = nullptr;
      }
      m_map.clear();
    }

    template <int I>
    QTimer* hertz() const {
      if (!m_map.contains(I)) {
        static_assert(0 < I && I <= 600, "fps out of range.");
        QTimer* timer = new QTimer(m_parent);
        timer->start(1000 / I);
        m_map[I] = timer;
      }
      return m_map[I];
    };
  };

  MainWindow* m_gui;
  std::unique_ptr<Timers> m_timers;

 public:
  ModulesPrivate(MainWindow* gui);

  MainWindow* gui() const;
  Timers* timers() const;

 signals:
  void rebuild();
  void setup();

 public slots:
  void onPlayPauseButtonPressed(bool isRunning);

 protected:
  template <class T, class F>
  class Maker {
    static_assert(std::is_base_of_v<ModuleBase, T>);

    T*& ref;
    F factory;

    static void deleteIfExists(T* instance) {
      if (instance) {
        qWarning().nospace()
            << "scheduling the deletion of " << instance << ".";
        static_cast<QObject*>(instance)->deleteLater();
      }
    }

    static void setup(T* instance, Modules* modules) {
      qWarning() << "performing" << instance << "setup.";
      static_cast<ModuleBase*>(instance)->setup(modules);
    }

    /* connecting updates, (TODO: painting) and building dialog before object
     * build. Trazer pra dentro da classe.
     */
    inline static void setDefaultConnections(T* ref, MainWindow* gui) {
      ModuleBox* moduleBox = gui->moduleBox(Utils::nameOfType<T>());

      QObject::connect(ref,
                       &ModuleBase::sendParameters,
                       moduleBox->dialog(),
                       &ParametersDialog::build);

      QObject::connect(moduleBox->dialog(),
                       &ParametersDialog::onChangingParameters,
                       ref,
                       &ModuleBase::receiveUpdateRequests);
    }

    static void build(T*& ref,
                      const F& factory,
                      Modules* modules,
                      MainWindow* gui,
                      QThreadPool* threadPool) {
      qWarning().nospace() << "building " << Utils::nameOfType<T>() << ".";

      deleteIfExists(ref);

      ModuleBox* moduleBox = gui->moduleBox(Utils::nameOfType<T>());
      QString type = moduleBox->currentText();
      ref = factory[type](threadPool);

      qWarning().nospace() << "a new instance of " << Utils::nameOfType<T>()
                           << " with type " << type << " was created: " << ref
                           << ".";

      setDefaultConnections(ref, gui); // ir pra dentro da classe.

      static_cast<ModuleBase*>(ref)->build();

      QObject::connect(modules,
                       &ModulesPrivate::setup,
                       ref,
                       std::bind(Maker::setup, ref, modules));
    }

    static void
    setToolTip(ModuleBox* moduleBox, const F& factory, const QString& type) {
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
                     Modules* modules,
                     MainWindow* gui,
                     QThreadPool* threadPool) {
      ModuleBox* moduleBox = gui->moduleBox(Utils::nameOfType<T>());
      QString type = moduleBox->currentText();

      build(ref, factory, modules, gui, threadPool);
      setToolTip(moduleBox, factory, type);
    }

   public:
    Maker(T*& t_ref, const F& t_factory) : ref(t_ref), factory(t_factory) {
    }

    void
    operator()(Modules* modules, MainWindow* gui, QThreadPool* threadPool) {
      if (factory.empty()) {
        return;
      }
      qWarning().nospace() << "making " << Utils::nameOfType<T>() << "...";
      ModuleBox* moduleBox = gui->moduleBox(Utils::nameOfType<T>());
      //
      QObject::connect(moduleBox,
                       &ModuleBox::onCurrentTextChanged,
                       modules,
                       std::bind(Maker::make,
                                 std::ref(ref),
                                 factory,
                                 modules,
                                 gui,
                                 threadPool));
      //
      QObject::connect(modules,
                       &ModulesPrivate::rebuild,
                       modules,
                       std::bind(Maker::build,
                                 std::ref(ref),
                                 factory,
                                 modules,
                                 gui,
                                 threadPool));
      //
      moduleBox->setComboBoxItems(factory.keys());
    }
  };

 private:
  void clear();
};

#endif // MODULESPRIVATE_H
