#ifndef SOCCER_COMMON_MENUBAROPTIONS_H
#define SOCCER_COMMON_MENUBAROPTIONS_H

#include <QtWidgets>

class MainWindowMenuBar;

class MenuBarOptions {
  QList<MenuBarOptions*> widgets;

 protected:
  virtual void putWidgetActions(MainWindowMenuBar& menubar) = 0;
  void setupMenuBar(MainWindowMenuBar& menubar);

 public:
  explicit MenuBarOptions(MenuBarOptions* parent = nullptr);
};

#endif // SOCCER_COMMON_MENUBAROPTIONS_H
