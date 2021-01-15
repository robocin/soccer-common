#include "RobotWidgets.h"
#include "ui_RobotWidgets.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RobotWidgets::RobotWidgets(QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::RobotWidgets),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

RobotWidgets::~RobotWidgets() {
  delete ui;
}

void RobotWidgets::showBatteryCharger(int level) {
  ui->batteryCharger->setValue(level);
}
void RobotWidgets::showCapacitorCharger(int level) {
  ui->capacitorCharger->setValue(level);
}
void RobotWidgets::writeLocalSettings(QSettings& settings) {
  settings.setValue("batteryCharger", ui->batteryCharger->value());
  settings.setValue("capacitorCharger", ui->capacitorCharger->value());
  settings.setValue("viewAction", viewAction->isChecked());
}
void RobotWidgets::loadLocalSettings(const QSettings& settings) {
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
void RobotWidgets::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
