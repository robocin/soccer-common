#ifndef SOCCER_COMMON_MODULESWIDGETS_H
#define SOCCER_COMMON_MODULESWIDGETS_H

#include <QMap>
#include <QString>
#include <QScrollArea>

class ModuleBox;
class MainWindow;
class PlayPauseWidget;

class ModulesWidgets {
  QLayout* m_layout;
  MainWindow* m_mainWindow;
  PlayPauseWidget* m_playPauseWidget;
  QMap<QString, ModuleBox*> m_modules;

 protected:
  void setupModulesWidgets(MainWindow* mainWindow);

 public:
  ModulesWidgets() = default;

  ModuleBox* moduleBox(const QString& key);
  PlayPauseWidget* playPauseButton();
};

#endif // SOCCER_COMMON_MODULESWIDGETS_H
