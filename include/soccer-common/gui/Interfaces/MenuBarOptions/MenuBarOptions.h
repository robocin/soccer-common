#ifndef MENUBAROPTIONS_H
#define MENUBAROPTIONS_H

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

#endif // MENUBAROPTIONS_H
