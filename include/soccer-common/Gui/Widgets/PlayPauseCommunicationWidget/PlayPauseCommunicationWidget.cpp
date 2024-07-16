#include "PlayPauseCommunicationWidget.h"
#include "ui_PlayPauseCommunicationWidget.h"

#include <QDebug>
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

PlayPauseCommunicationWidget::PlayPauseCommunicationWidget(
    QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::PlayPauseCommunicationWidget) {
  ui->setupUi(this);
  ui->pushButton->setText("⏸️");
}

PlayPauseCommunicationWidget::~PlayPauseCommunicationWidget() {
  delete ui;
}

bool PlayPauseCommunicationWidget::isClicked() const {
  return ui->pushButton->isChecked();
}

void PlayPauseCommunicationWidget::click() {
  ui->pushButton->click();
}

void PlayPauseCommunicationWidget::setRunning(bool runningState) {
  if (runningState ^ isClicked()) {
    click();
  }
}

void PlayPauseCommunicationWidget::on_pushButton_clicked(bool checked) {
  if (checked) {
    ui->pushButton->setText("⏸️");
  } else {
    ui->pushButton->setText("▶️");
  }
  emit onPushButtonClicked(checked);
}

void PlayPauseCommunicationWidget::writeLocalSettings(QSettings&) {
}

void PlayPauseCommunicationWidget::loadLocalSettings(const QSettings&) {
}

void PlayPauseCommunicationWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  QAction* playPauseCommunication = new QAction("Play/Pause Communication", &menubar["File"]);
  playPauseCommunication->setShortcut(QKeySequence("Ctrl+L"));
  QObject::connect(playPauseCommunication, &QAction::triggered, this, [this]() {
    ui->pushButton->click();
  });
  menubar["File"].addAction(playPauseCommunication);
}
