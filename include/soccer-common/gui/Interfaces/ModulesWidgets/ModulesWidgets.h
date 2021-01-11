#ifndef MODULESWIDGETS_H
#define MODULESWIDGETS_H

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
  explicit ModulesWidgets();

  ModuleBox* moduleBox(const QString& key);
  PlayPauseWidget* playPauseButton();
};

#endif // MODULESWIDGETS_H
