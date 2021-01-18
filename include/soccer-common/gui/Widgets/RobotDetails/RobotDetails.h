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

class RobotDetails : public QWidget,
                     public WidgetSettings,
                     public MenuBarOptions {
  Q_OBJECT

 public:
  explicit RobotDetails(
      int index,
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~RobotDetails();
 public slots:
  void showBatteryCharger(int level);
  void showCapacitorCharger(int level);
  void showRobotNumber(int number);

 private:
  Ui::RobotDetails* ui;
  QAction* viewAction;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // RobotDetails_H
