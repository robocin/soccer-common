#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

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

#endif // SCOREBOARD_H
