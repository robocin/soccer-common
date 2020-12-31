#include "ModulesWidgets.h"

#include "soccer-common/gui/Widgets/Widgets.h"
#include "soccer-common/gui/MainWindow/MainWindow.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"

void ModulesWidgets::setupModulesWidgets(MainWindow* mainWindow) {
  m_mainWindow = mainWindow;

  /* creating scroll area */ {
    auto scrollArea = Factory::scrollAreaForFlowLayout(mainWindow);
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
    auto moduleBox = new ModuleBox(key, m_mainWindow);
    /* adding before play pause widget */ {
      m_layout->removeWidget(m_playPauseWidget);
      m_layout->addWidget(moduleBox);
      m_layout->addWidget(m_playPauseWidget);
    }
    m_modules[key] = moduleBox;
    QObject::connect(m_playPauseWidget,
                     &PlayPauseWidget::onPushButtonClicked,
                     moduleBox,
                     [moduleBox](bool clicked) {
                       moduleBox->setComboBoxEnabled(!clicked);
                     });
  }
  return m_modules[key];
}

PlayPauseWidget* ModulesWidgets::playPauseButton() {
  return m_playPauseWidget;
}
