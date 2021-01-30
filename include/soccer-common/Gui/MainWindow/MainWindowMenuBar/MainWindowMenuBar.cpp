#include "MainWindowMenuBar.h"

MainWindowMenuBar::MainWindowMenuBar(QMainWindow* mainWindow) :
    m_menuBar(new QMenuBar(mainWindow)) {
  if (mainWindow) {
    mainWindow->setMenuBar(m_menuBar);
  }
  /* this order matters */ {
    operator[]("File");
    operator[]("View");
  }
}

QMenuBar* MainWindowMenuBar::menuBar() const {
  return m_menuBar;
}

MainWindowMenuBar::MappedMenu&
MainWindowMenuBar::operator[](const QString& key) {
  if (m_map.find(key) == m_map.end()) {
    m_map[key] = new MappedMenu(key, m_menuBar);
  }
  return *m_map[key];
}
