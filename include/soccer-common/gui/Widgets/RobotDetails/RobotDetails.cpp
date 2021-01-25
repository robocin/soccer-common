#include "RobotDetails.h"
#include "ui_RobotDetails.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RobotDetails::RobotDetails(int index, QWidgetWith<WidgetSettings> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    ui(new Ui::RobotDetails) {
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
  QGraphicsScene* scene;
  scene = new QGraphicsScene(this);
  ui->robotID->setScene(scene);
  QGraphicsSvgItem* id = new QGraphicsSvgItem(":/robotID2.svg", scene);
  id->setParent(scene);
  scene->addItem(id);
  scene->setSceneRect((number * 512), 0, 512, 512);
}

void RobotDetails::ConnectCapacitorViewAction(QAction* action) {
  Factory::connectWithToggleViewAction(action, ui->capacitorWidget);
}

void RobotDetails::ConnectIrViewAction(QAction* action) {
  Factory::connectWithToggleViewAction(action, ui->irTitle);
}

void RobotDetails::connectBatteryViewAction(QAction* action) {
  Factory::connectWithToggleViewAction(action, ui->batteyWidget);
}
void RobotDetails::writeLocalSettings(QSettings& settings) {
  settings.setValue("batteryCharger", ui->batteryCharger->value());
  settings.setValue("capacitorCharger", ui->capacitorCharger->value());
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
  showBatteryCharger(batteryLevel);
  showCapacitorCharger(capacitorLevel);
}
