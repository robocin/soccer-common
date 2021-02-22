#include "PlayPauseWidget.h"
#include "ui_PlayPauseWidget.h"

#include <QDebug>
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

PlayPauseWidget::PlayPauseWidget(QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::PlayPauseWidget) {
  ui->setupUi(this);
}

PlayPauseWidget::~PlayPauseWidget() {
  delete ui;
}

bool PlayPauseWidget::isClicked() const {
  return ui->pushButton->isChecked();
}

void PlayPauseWidget::click() {
  ui->pushButton->click();
}

void PlayPauseWidget::setRunning(bool runningState) {
  if (runningState ^ isClicked()) {
    click();
  }
}

void PlayPauseWidget::on_pushButton_clicked(bool checked) {
  if (checked) {
    ui->pushButton->setText("⏸️");
  } else {
    ui->pushButton->setText("▶️");
  }
  emit onPushButtonClicked(checked);
}

void PlayPauseWidget::writeLocalSettings(QSettings&) {
}

void PlayPauseWidget::loadLocalSettings(const QSettings&) {
}

void PlayPauseWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  QAction* playPause = new QAction("Play/Pause", &menubar["File"]);
  playPause->setShortcut(QKeySequence("Ctrl+R"));
  QObject::connect(playPause, &QAction::triggered, this, [this]() {
    ui->pushButton->click();
  });
  menubar["File"].addAction(playPause);
}
