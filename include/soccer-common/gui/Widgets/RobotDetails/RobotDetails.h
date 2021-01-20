#ifndef ROBOTDETAILS_H
#define ROBOTDETAILS_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

namespace Ui {
  class RobotDetails;
}

class RobotDetails : public QWidget, public WidgetSettings {
  Q_OBJECT
  friend class RobotsWidgets;

 public:
  explicit RobotDetails(int index,
                        QWidgetWith<WidgetSettings> parent = nullptr);
  ~RobotDetails();
 public slots:
  void showBatteryCharger(int level);
  void showCapacitorCharger(int level);
  void showRobotNumber(int number);

  // void ConnectCapacitorViewAction();
  // void ConnectIrViewAction();

 private:
  Ui::RobotDetails* ui;

  void connectBatteryViewAction(QAction* action);
  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;
};

#endif // RobotDetails_H
