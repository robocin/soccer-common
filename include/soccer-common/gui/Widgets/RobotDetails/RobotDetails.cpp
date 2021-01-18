#include "RobotDetails.h"
#include "ui_RobotDetails.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RobotDetails::RobotDetails(int index,
                           QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::RobotDetails),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
  showRobotNumber(index);
}

RobotDetails::~RobotDetails() {
  delete ui;
}

void RobotDetails::showBatteryCharger(int level) {
  ui->batteryCharger->setValue(level);
}
void RobotDetails::showCapacitorCharger(int level) {
  ui->capacitorCharger->setValue(level);
}
void RobotDetails::showRobotNumber(int number) {
  ui->robotNumber->setText(QString::number(number));
}
void RobotDetails::writeLocalSettings(QSettings& settings) {
  settings.setValue("batteryCharger", ui->batteryCharger->value());
  settings.setValue("capacitorCharger", ui->capacitorCharger->value());
  settings.setValue("viewAction", viewAction->isChecked());
}
void RobotDetails::loadLocalSettings(const QSettings& settings) {
  int batteryLevel = 100;
  int capacitorLevel = 100;
  if (settings.contains("batteryCharger")) {
    QString savedBatteryCharger =
        settings.value("batteryCharger").value<QString>();
    batteryLevel = savedBatteryCharger.toInt();
  }
  if (settings.contains("capacitorCharger")) {
    QString savedCapacitorCharger =
        settings.value("capacitorCharger").value<QString>();
    capacitorLevel = savedCapacitorCharger.toInt();
  }
  if (settings.contains("viewAction")) {
    bool view = settings.value("viewAction").value<bool>();
    viewAction->setChecked(view);
  }
  showBatteryCharger(batteryLevel);
  showCapacitorCharger(capacitorLevel);
}
void RobotDetails::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
