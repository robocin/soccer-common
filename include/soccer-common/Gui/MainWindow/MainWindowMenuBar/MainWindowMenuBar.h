#ifndef SOCCER_COMMON_MAINWINDOWMENUBAR_H
#define SOCCER_COMMON_MAINWINDOWMENUBAR_H

#include <QtWidgets>

class MainWindowMenuBar {
  class MappedMenu : public QMenu {
    std::map<QString, MappedMenu*> m_map;

   public:
    explicit MappedMenu(const QString& title, QMenuBar* parent) :
        QMenu(title, parent) {
      Q_ASSERT(parent != nullptr);
      parent->addMenu(this);
    }

    explicit MappedMenu(const QString& title, MappedMenu* parent) :
        QMenu(title, parent) {
      Q_ASSERT(parent != nullptr);
      parent->addMenu(this);
    }

    MappedMenu& operator[](const QString& key) {
      if (m_map.find(key) == m_map.end()) {
        m_map[key] = new MappedMenu(key, this);
      }
      return *m_map[key];
    }
  };
  QMenuBar* m_menuBar;
  std::map<QString, MappedMenu*> m_map;

 public:
  explicit MainWindowMenuBar(QMainWindow* mainWindow);

  QMenuBar* menuBar() const;
  MappedMenu& operator[](const QString& key);
};

#endif // SOCCER_COMMON_MAINWINDOWMENUBAR_H
