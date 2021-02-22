#include "MenuBarOptions.h"

void MenuBarOptions::setupMenuBar(MainWindowMenuBar& menubar) {
  putWidgetActions(menubar);
  for (auto widget : widgets) {
    widget->setupMenuBar(menubar);
  }
}

MenuBarOptions::MenuBarOptions(MenuBarOptions* parent) {
  if (parent) {
    parent->widgets += this;
  }
}
