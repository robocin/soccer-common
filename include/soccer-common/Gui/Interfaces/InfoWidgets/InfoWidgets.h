#ifndef SOCCER_COMMON_INFOWIDGETS_H
#define SOCCER_COMMON_INFOWIDGETS_H

#include <QScrollArea>

class MainWindow;

class ScoreboardWidget;
class AttackSideWidget;
class ColorTeamWidget;

class InfoWidgets {
  QLayout* m_layout{};
  ScoreboardWidget* m_scoreboard{};
  AttackSideWidget* m_attackSide{};
  ColorTeamWidget* m_colorTeam{};

 protected:
  void setupInfoWidgets(MainWindow* mainWindow);

 public:
  explicit InfoWidgets() = default;

  ScoreboardWidget* scoreboard() const;
  AttackSideWidget* attackSide() const;
  ColorTeamWidget* colorTeam() const;
};

#endif // SOCCER_COMMON_INFOWIDGETS_H
