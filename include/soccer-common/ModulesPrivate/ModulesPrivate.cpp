#include "ModulesPrivate.h"

ModulesPrivate::ModulesPrivate(MainWindow* gui) :
    m_gui(gui),
    m_timers(std::make_unique<Timers>(this)) {
  QObject::connect(gui->playPauseButton(),
                   &PlayPauseWidget::onPushButtonClicked,
                   this,
                   &ModulesPrivate::onPlayPauseButtonPressed);
}

MainWindow* ModulesPrivate::gui() const {
  return m_gui;
}

ModulesPrivate::Timers* ModulesPrivate::timers() const {
  return m_timers.get();
}

void ModulesPrivate::onPlayPauseButtonPressed(bool isRunning) {
  if (isRunning) {
    emit setup();
  } else {
    qDebug() << "starting rebuild...";
    clear();
    emit rebuild();
    qDebug() << "finish rebuild.";
  }
}

void ModulesPrivate::clear() {
  m_timers->clear();
}
