#include "RobotDetails.h"
#include "ui_RobotDetails.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RobotDetails::RobotDetails(int index,
                           const QString& robotsPatternPath,
                           QWidgetWith<WidgetSettings> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    ui(new Ui::RobotDetails) {
  ui->setupUi(this);
  showRobotNumber(index);
  showRobotPattern(index, robotsPatternPath, "blue");
  statusInfraRed(true); // trocar
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
  QPixmap pixmap(":/robotID.png");
  QGraphicsPixmapItem* id = new QGraphicsPixmapItem(pixmap);
  scene->addItem(id);
  scene->setSceneRect((number * 70), 0, 70, 70);
}

void RobotDetails::statusInfraRed(bool isOn) {
  QGraphicsScene* scene;
  scene = new QGraphicsScene(this);
  ui->irTitle->setScene(scene);
  QGraphicsPixmapItem* id;
  QPixmap pixmapOn(":/led_on.png");
  QPixmap pixmapOff(":/led_off.png");
  if (isOn) {
    id = new QGraphicsPixmapItem(pixmapOn);
  } else
    id = new QGraphicsPixmapItem(pixmapOff);
  scene->addItem(id);
  scene->setSceneRect(0, 0, 32, 35);
}

void RobotDetails::showRobotPattern(int number,
                                    const QString& robotsPatternPath,
                                    QString color) {
  QGraphicsScene* scene;
  QPixmap pixmap(robotsPatternPath);
  QColor background(color);
  QBrush brush(background);
  scene = new QGraphicsScene(this);
  ui->robotPattern->setScene(scene);
  QGraphicsPixmapItem* id = new QGraphicsPixmapItem(pixmap);
  scene->setBackgroundBrush(brush);
  scene->addItem(id);
  scene->setSceneRect((number * 70), 0, 70, 70);
}

/*
void RobotDetails::onColorChanged(QColor color) {
  showRobotPattern(number, robotsPatternPath, color);
}
*/

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
