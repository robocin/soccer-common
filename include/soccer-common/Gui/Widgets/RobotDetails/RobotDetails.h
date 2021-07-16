#ifndef SOCCER_COMMON_ROBOTDETAILS_H
#define SOCCER_COMMON_ROBOTDETAILS_H

#include <QtCore>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QtSvg/QSvgRenderer>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class RobotDetails;
}

class RobotDetails : public QWidget {
  Q_OBJECT
  friend class RobotsWidgets;

 public:
  explicit RobotDetails(int index, QWidget* parent = nullptr);
  ~RobotDetails() override;

 public slots:
  void setRobotColor(const QColor& color);

 private:
  Ui::RobotDetails* ui;

  int index;
  QColor color;
  QString robotsPatternPath;

  void setRobotsPatternPath(const QString& path);

  void setupRobotNumber();
  void setupRobot();
};

#endif // SOCCER_COMMON_ROBOTDETAILS_H
