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
  TabsWidget* m_tabsWidget{};

  [[nodiscard]] TabsWidget* tabsWidget() const;

 protected:
  void setMaxVisibleRobots(int n);
  void setupRobotsWidgets(MainWindow* mainWindow);
  void setupRobotsWidgetsPattern(const QString& path);

 public:
  explicit RobotsWidgets(int maxRobots);

  [[nodiscard]] int maxRobots() const;
  ModuleBox* indexedModuleBox(int index, const QString& key);

  void setRobotDetailsColor(const QColor& color);
};

#endif // SOCCER_COMMON_ROBOTSWIDGETS_H
