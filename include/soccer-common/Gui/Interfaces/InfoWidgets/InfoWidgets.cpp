#include "InfoWidgets.h"

#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

void InfoWidgets::setupInfoWidgets(MainWindow* mainWindow) {
  /* creating scroll area layout */ {
    auto scrollArea = Factory::scrollAreaWithFlowLayout(mainWindow);
    mainWindow->dockWidgetInfoContents()->layout()->addWidget(scrollArea);
    m_layout = scrollArea->widget()->layout();
  }

  /* adding scoreboard */ {
    m_scoreboard = new ScoreboardWidget(mainWindow);
    m_layout->addWidget(m_scoreboard);
  }
  /* adding attack side */ {
    m_attackSide = new AttackSideWidget(mainWindow);
    m_layout->addWidget(m_attackSide);
  }
  /* adding color team */ {
    m_colorTeam = new ColorTeamWidget(mainWindow);
    m_layout->addWidget(m_colorTeam);
  }
}

InfoWidgets::InfoWidgets() {
}

ScoreboardWidget* InfoWidgets::scoreboard() const {
  return m_scoreboard;
}

AttackSideWidget* InfoWidgets::attackSide() const {
  return m_attackSide;
}

ColorTeamWidget* InfoWidgets::colorTeam() const {
  return m_colorTeam;
}
