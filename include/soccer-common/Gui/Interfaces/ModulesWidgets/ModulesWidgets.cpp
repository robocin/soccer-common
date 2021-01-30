#include "ModulesWidgets.h"

#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

void ModulesWidgets::setupModulesWidgets(MainWindow* mainWindow) {
  m_mainWindow = mainWindow;

  /* creating scroll area */ {
    auto scrollArea = Factory::scrollAreaWithFlowLayout(mainWindow);
    mainWindow->dockWidgetModulesContents()->layout()->addWidget(scrollArea);
    m_layout = scrollArea->widget()->layout();
  }
  /* adding play/pause widget */ {
    m_playPauseWidget = new PlayPauseWidget(m_mainWindow);
    m_layout->addWidget(m_playPauseWidget);
  }
}

ModulesWidgets::ModulesWidgets() {
}

ModuleBox* ModulesWidgets::moduleBox(const QString& key) {
  if (!m_modules.contains(key)) {
    auto moduleBox = Factory::moduleBox(key, m_mainWindow);
    /* adding before play pause widget */ {
      m_layout->removeWidget(m_playPauseWidget);
      m_layout->addWidget(moduleBox);
      m_layout->addWidget(m_playPauseWidget);
    }
    m_modules[key] = moduleBox;
  }
  return m_modules[key];
}

PlayPauseWidget* ModulesWidgets::playPauseButton() {
  return m_playPauseWidget;
}
