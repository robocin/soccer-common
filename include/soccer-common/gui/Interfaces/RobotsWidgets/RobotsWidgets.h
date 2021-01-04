#ifndef ROBOTSWIDGETS_H
#define ROBOTSWIDGETS_H

#include <QMap>
#include <QTabWidget>
#include <QScrollArea>

class ModuleBox;
class MainWindow;

class RobotsWidgets {
  int m_maxRobots;
  class TabsWidget;
  TabsWidget* tabsWidget;

 protected:
  void setupRobotsWidgets(MainWindow* mainWindow);

 public:
  explicit RobotsWidgets(int maxRobots = 11);

  int maxRobots() const;
  ModuleBox* indexedModuleBox(int index, const QString& key);
};

#endif // ROBOTSWIDGETS_H
