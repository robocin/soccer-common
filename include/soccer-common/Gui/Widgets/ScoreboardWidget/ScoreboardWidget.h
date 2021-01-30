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

class ScoreboardWidget : public QWidget,
                         public WidgetSettings,
                         public MenuBarOptions {
  Q_OBJECT

 public:
  explicit ScoreboardWidget(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~ScoreboardWidget();

 public slots:
  void setFirstTeamColor(const QColor& color);
  void setSecondTeamColor(const QColor& color);
  void setScore(int first, int second);

 private:
  Ui::ScoreboardWidget* ui;
  QAction* viewAction;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_SCOREBOARD_H
