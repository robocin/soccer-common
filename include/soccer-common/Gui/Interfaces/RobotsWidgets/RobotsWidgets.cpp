#include "RobotsWidgets.h"

#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

// to do.
// class RobotDetails;

class RobotsWidgets::TabsWidget : public WidgetSettings, public MenuBarOptions {
  static constexpr const char* robotDetailsLayout = "Details";

  class Robot : public WidgetSettings {
    using RobotDetails = QLabel; // to do: replace with robot widget.

    int index;
    QMap<QString, QLayout*>& layouts;

    MainWindow* mainWindow;

    RobotDetails* robotDetails; // to do.
    QMap<QString, ModuleBox*> modules;

   public:
    Robot(int index, QMap<QString, QLayout*>& layouts, MainWindow* mainWindow) :
        WidgetSettings(QString("Robot%1").arg(index, 2, 10, QChar('0')),
                       mainWindow),
        index(index),
        layouts(layouts),
        mainWindow(mainWindow) {
      /* build robotWidget */ {
        robotDetails = new QLabel(mainWindow);
        robotDetails->setAlignment(Qt::AlignmentFlag::AlignCenter);
        robotDetails->setText(
            "to do: " + QString("Robot %1").arg(index, 2, 10, QChar('0')) +
            " details.");
        layouts[robotDetailsLayout]->addWidget(robotDetails);
      }
    }

    RobotDetails* details() const {
      return robotDetails;
    }

    ModuleBox* moduleBox(const QString& key) {
      if (!modules.contains(key)) {
        auto moduleBox =
            Factory::moduleBox((key + " %1").arg(index, 2, 10, QChar('0')),
                               mainWindow,
                               this);
        layouts[key]->addWidget(moduleBox);
        modules[key] = moduleBox;
      }
      return modules[key];
    }

   protected:
    void writeLocalSettings(QSettings&) override {
      // to do: robotWidget visual setings.
    }
    void loadLocalSettings(const QSettings&) override {
      // to do: robotWidget visual setings.
    }
  };

  QMenu* m_menu;
  QVector<Robot*> m_robots;

  QTabWidget* m_tabWidget;
  QMap<QString, QLayout*> m_layouts;

 public:
  TabsWidget(int maxRobots, MainWindow* mainWindow) :
      WidgetSettings(Utils::nameOfType<RobotsWidgets>(), mainWindow),
      MenuBarOptions(mainWindow),
      m_menu(new QMenu("Robots", mainWindow)),
      m_tabWidget(new QTabWidget(mainWindow)) {
    /* building RobotDetails layout. */ {
      auto widget = Factory::scrollAreaWithFlowLayout(m_tabWidget);
      auto layout = widget->widget()->layout();
      m_tabWidget->addTab(widget, robotDetailsLayout);
      m_layouts[robotDetailsLayout] = layout;
    }
    for (int i = 0; i < maxRobots; ++i) {
      m_robots.push_back(new Robot(i, m_layouts, mainWindow));
    }
    mainWindow->dockWidgetRobotsContents()->layout()->addWidget(m_tabWidget);
  }

  ModuleBox* moduleBox(int pos, const QString& key) {
    if (!m_layouts.contains(key)) {
      auto widget = Factory::scrollAreaWithFlowLayout(m_tabWidget);
      auto layout = widget->widget()->layout();
      int tabId = m_tabWidget->addTab(widget, key);
      m_layouts[key] = layout;
      //
      m_menu->addAction(Factory::toggleViewAction(key, tabId, m_tabWidget));
      //
      for (int i = 0; i < m_robots.size(); ++i) {
        m_robots[i]->moduleBox(key);
      }
    }
    return m_robots[pos]->moduleBox(key);
  }

  void writeLocalSettings(QSettings& settings) override {
    /* tab widget current index */ {
      int currentIndex = m_tabWidget->currentIndex();
      settings.setValue("tabWidgetCurrentIndex", currentIndex);
    }

    auto actions = m_menu->actions();
    for (auto viewAction : actions) {
      settings.setValue(viewAction->text() + "ViewAction",
                        viewAction->isChecked());
    }
  }

  void loadLocalSettings(const QSettings& settings) override {
    if (settings.contains("tabWidgetCurrentIndex")) {
      int currentIndex = settings.value("tabWidgetCurrentIndex").value<int>();
      m_tabWidget->setCurrentIndex(currentIndex);
    }

    auto actions = m_menu->actions();
    for (auto viewAction : actions) {
      QString text = viewAction->text() + "ViewAction";
      if (settings.contains(text)) {
        bool view = settings.value(text).value<bool>();
        viewAction->setChecked(view);
      }
    }
  }

  void putWidgetActions(MainWindowMenuBar& menubar) override {
    menubar["View"].addMenu(m_menu);
  }
};

void RobotsWidgets::setupRobotsWidgets(MainWindow* mainWindow) {
  tabsWidget = new TabsWidget(m_maxRobots, mainWindow);
}

RobotsWidgets::RobotsWidgets(int maxRobots) : m_maxRobots(maxRobots) {
}

int RobotsWidgets::maxRobots() const {
  return m_maxRobots;
}

ModuleBox* RobotsWidgets::indexedModuleBox(int index, const QString& key) {
  return tabsWidget->moduleBox(index, key);
}
