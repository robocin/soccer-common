#ifndef SOCCER_COMMON_ROBOTSWIDGETS_H
#define SOCCER_COMMON_ROBOTSWIDGETS_H

#include <QMap>
#include <QTabWidget>
#include <QScrollArea>

class ModuleBox;
class MainWindow;

class RobotsWidgets {
  int m_maxRobots;
  class TabsWidget;
  TabsWidget* tabsWidget{};

 protected:
  void setupRobotsWidgets(MainWindow* mainWindow);

 public:
  explicit RobotsWidgets(int maxRobots);

  int maxRobots() const;
  ModuleBox* indexedModuleBox(int index, const QString& key);
};

#endif // SOCCER_COMMON_ROBOTSWIDGETS_H
