#ifndef SSL_UNIFICATION_MODULESWIDGETS_H
#define SSL_UNIFICATION_MODULESWIDGETS_H

#include <QMap>
#include <QString>
#include <QScrollArea>

class ModuleBox;
class MainWindow;
class PlayPauseWidget;
class PlayPauseCommunicationWidget;

class ModulesWidgets {
  QLayout* m_layout;
  MainWindow* m_mainWindow;
  PlayPauseWidget* m_playPauseWidget;
  PlayPauseCommunicationWidget* m_playPauseCommunicationWidget;
  QMap<QString, ModuleBox*> m_modules;

 protected:
  void setupModulesWidgets(MainWindow* mainWindow);

 public:
  ModulesWidgets() = default;

  ModuleBox* moduleBox(const QString& key);
  PlayPauseWidget* playPauseButton();
  PlayPauseCommunicationWidget* playPauseCommunicationButton();
};

#endif // SSL_UNIFICATION_MODULESWIDGETS_H
