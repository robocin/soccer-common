#include "ModulesPrivate.h"

ModulesPrivate::ModulesPrivate(MainWindow* gui) :
    m_gui(gui),
    m_modulesThread(new QThread(this)),
    m_timers(m_modulesThread) {
  m_modulesThread->start();

  QObject::connect(gui->playPauseButton(),
                   &PlayPauseWidget::onPushButtonClicked,
                   this,
                   &ModulesPrivate::onPlayPauseButtonPressed);

  QObject::connect(this,
                   &QObject::destroyed,
                   m_modulesThread,
                   &QObject::deleteLater);
}

ModulesPrivate::~ModulesPrivate() {
}

MainWindow* ModulesPrivate::gui() const {
  return m_gui;
}

ModulesPrivate::Timers* ModulesPrivate::timers() const {
  return &const_cast<Timers&>(m_timers);
}

void ModulesPrivate::onPlayPauseButtonPressed(bool isRunning) {
  if (isRunning) {
    emit setup();
    emit impulse();
  } else {
    qDebug() << "starting rebuild...";
    clear();
    emit rebuild();
    qDebug() << "finish rebuild.";
  }
}

QThread* ModulesPrivate::modulesThread() const {
  return m_modulesThread;
}

void ModulesPrivate::clear() {
  m_timers.clear();
}
