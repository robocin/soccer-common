#include "RobotsWidgets.h"

#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

class RobotsWidgets::TabsWidget : public WidgetSettings, public MenuBarOptions {
  static constexpr const char* robotDetailsLayout = "Details";

  class Robot : public WidgetSettings {

    int index;
    QMap<QString, QLayout*>& layouts;

    MainWindow* mainWindow;
    RobotDetails* robotDetails;
    QMap<QString, ModuleBox*> modules;

   public:
    Robot(int index, QMap<QString, QLayout*>& layouts, MainWindow* mainWindow) :
        WidgetSettings(QString("Robot%1").arg(index, 2, 10, QChar('0')), mainWindow),
        index(index),
        layouts(layouts),
        mainWindow(mainWindow),
        robotDetails(new RobotDetails(index, mainWindow)) {
      layouts[robotDetailsLayout]->addWidget(robotDetails);
    }

    [[nodiscard]] RobotDetails* details() const {
      return robotDetails;
    }

    [[nodiscard]] QMap<QString, ModuleBox*>& modulesMap() {
      return modules;
    }

    ModuleBox* moduleBox(const QString& key) {
      if (!modules.contains(key)) {
        auto moduleBox =
            Factory::moduleBox((key + " %1").arg(index, 2, 10, QChar('0')), mainWindow, this);
        layouts[key]->addWidget(moduleBox);
        modules[key] = moduleBox;
      }
      return modules[key];
    }

   protected:
    void writeLocalSettings(QSettings&) override {
    }
    void loadLocalSettings(const QSettings&) override {
    }
  };

  QMenu* m_menu;
  QVector<Robot*> m_robots;

  int m_maxVisibleRobots;

  QTabWidget* m_tabWidget;
  QMap<QString, QLayout*> m_layouts;

 public:
  TabsWidget(int maxRobots, MainWindow* mainWindow) :
      WidgetSettings(Utils::nameOfType<RobotsWidgets>(), mainWindow),
      MenuBarOptions(mainWindow),
      m_menu(new QMenu("Robots", mainWindow)),
      m_tabWidget(new QTabWidget(mainWindow)),
      m_maxVisibleRobots(maxRobots) {
    /* building RobotDetails layout. */ {
      auto widget = Factory::scrollAreaWithFlowLayout(m_tabWidget);
      auto layout = widget->widget()->layout();
      m_tabWidget->addTab(widget, robotDetailsLayout);
      m_layouts[robotDetailsLayout] = layout;
    }
    for (int i = 0; i < maxRobots; ++i) {
      m_robots.emplace_back(new Robot(i, m_layouts, mainWindow));
    }
    mainWindow->dockWidgetRobotsContents()->layout()->addWidget(m_tabWidget);
  }

  void setRobotsPatternPath(const QString& path) {
    for (auto& robot : m_robots) {
      robot->details()->setRobotsPatternPath(path);
    }
  }

  void setRobotsPatternColor(const QColor& color) {
    for (auto& robot : m_robots) {
      robot->details()->setRobotColor(color);
    }
  }

  void setMaxVisibleRobots(int n) {
    m_maxVisibleRobots = n;
    int maxRobots = static_cast<int>(m_robots.size());
    for (int i = 0; i < n; ++i) {
      m_robots[i]->details()->show();
      for (auto& m : m_robots[i]->modulesMap()) {
        m->show();
      }
    }
    for (int i = n; i < maxRobots; ++i) {
      m_robots[i]->details()->hide();
      for (auto& m : m_robots[i]->modulesMap()) {
        m->hide();
      }
    }
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
      for (auto& robot : m_robots) {
        robot->moduleBox(key);
      }
    }
    return m_robots[pos]->moduleBox(key);
  }

 private:
  void writeLocalSettings(QSettings& settings) override {
    /* tab widget current index */ {
      int currentIndex = m_tabWidget->currentIndex();
      settings.setValue("tabWidgetCurrentIndex", currentIndex);
    }

    settings.setValue("Max Visible Robots", m_maxVisibleRobots);

    auto actions = m_menu->actions();
    for (auto viewAction : actions) {
      settings.setValue(viewAction->text() + "ViewAction", viewAction->isChecked());
    }
  }

  void loadLocalSettings(const QSettings& settings) override {
    if (settings.contains("tabWidgetCurrentIndex")) {
      int currentIndex = settings.value("tabWidgetCurrentIndex").value<int>();
      m_tabWidget->setCurrentIndex(currentIndex);
    }

    if (settings.contains("Max Visible Robots")) {
      setMaxVisibleRobots(settings.value("Max Visible Robots").value<int>());
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

RobotsWidgets::TabsWidget* RobotsWidgets::tabsWidget() const {
  if (m_tabsWidget) {
    return m_tabsWidget;
  } else {
    throw std::runtime_error("robot tabs widget is null");
  }
}

void RobotsWidgets::setMaxVisibleRobots(int n) {
  tabsWidget()->setMaxVisibleRobots(n);
}

void RobotsWidgets::setupRobotsWidgets(MainWindow* mainWindow) {
  m_tabsWidget = new TabsWidget(m_maxRobots, mainWindow);
}

void RobotsWidgets::setupRobotsWidgetsPattern(const QString& path) {
  tabsWidget()->setRobotsPatternPath(path);
}

RobotsWidgets::RobotsWidgets(int maxRobots) : m_maxRobots(maxRobots) {
}

int RobotsWidgets::maxRobots() const {
  return m_maxRobots;
}

ModuleBox* RobotsWidgets::indexedModuleBox(int index, const QString& key) {
  return tabsWidget()->moduleBox(index, key);
}

void RobotsWidgets::setRobotDetailsColor(const QColor& color) {
  tabsWidget()->setRobotsPatternColor(color);
}
