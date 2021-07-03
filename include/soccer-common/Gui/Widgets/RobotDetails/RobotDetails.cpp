#include "RobotDetails.h"
#include "ui_RobotDetails.h"

#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RobotDetails::RobotDetails(int index, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RobotDetails),
    index(index),
    color(Color::Black) {
  ui->setupUi(this);
  setupRobotNumber();
}

RobotDetails::~RobotDetails() {
  delete ui;
}

void RobotDetails::setupRobotNumber() {
  ui->robotId->setTitle(QString("Robot %1").arg(index, 2));
}

void RobotDetails::setRobotColor(const QColor& c) {
  color = c;
  setupRobot();
}

void RobotDetails::setRobotsPatternPath(const QString& path) {
  robotsPatternPath = path;
  setupRobot();
}

void RobotDetails::setupRobot() {
  QGraphicsScene* scene;
  QPixmap pixmap(robotsPatternPath);
  QColor background(color);
  QBrush brush(background);
  scene = new QGraphicsScene(this);
  ui->robotPattern->setScene(scene);
  auto* id = new QGraphicsPixmapItem(pixmap);
  scene->setBackgroundBrush(brush);
  scene->addItem(id);
  scene->setSceneRect((index * 70), 0, 70, 70);
}
