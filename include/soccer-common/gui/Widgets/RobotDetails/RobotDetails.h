#ifndef ROBOTDETAILS_H
#define ROBOTDETAILS_H

#include <QtCore>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QtSvg/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

namespace Ui {
  class RobotDetails;
}

class RobotDetails : public QWidget, public WidgetSettings {
  Q_OBJECT
  friend class RobotsWidgets;

  int index;
  QString robotsPatternPath;

 public:
  explicit RobotDetails(int index, const QString &robotsPatternPath,
                        QWidgetWith<WidgetSettings> parent = nullptr);
  ~RobotDetails();
 public slots:
  void showBatteryCharger(int level);
  void showCapacitorCharger(int level);
  void showRobotNumber(int number);
  void statusInfraRed(bool isOn);
  void showRobotPattern(int number, const QString &robotsPatternPath, QString color);
  void ConnectCapacitorViewAction(QAction* action);
  void ConnectIrViewAction(QAction* action);
 private:
  Ui::RobotDetails* ui;

  void connectBatteryViewAction(QAction* action);
  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;
};

#endif // RobotDetails_H
