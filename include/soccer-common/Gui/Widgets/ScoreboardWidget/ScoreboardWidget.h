#ifndef SOCCER_COMMON_SCOREBOARD_H
#define SOCCER_COMMON_SCOREBOARD_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class ScoreboardWidget;
}

class ScoreboardWidget : public QWidget, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit ScoreboardWidget(QWidgetWith<MenuBarOptions> parent = nullptr);
  ~ScoreboardWidget() override;

 public slots:
  void setColor(const QColor& firstColor, const QColor& secondColor);
  void setScore(int first, int second);

 private:
  Ui::ScoreboardWidget* ui;
  QAction* viewAction;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_SCOREBOARD_H
