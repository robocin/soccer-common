#ifndef ROBOTWIDGETS_H
#define ROBOTWIDGETS_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

namespace Ui {
  class RobotWidgets;
}

class RobotWidgets : public QWidget,
                     public WidgetSettings,
                     public MenuBarOptions {
  Q_OBJECT

 public:
  explicit RobotWidgets(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~RobotWidgets();
 public slots:
  void showBatteryCharger(int level);
  void showCapacitorCharger(int level);

 private:
  Ui::RobotWidgets* ui;
  QAction* viewAction;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // RobotWidgets_H
