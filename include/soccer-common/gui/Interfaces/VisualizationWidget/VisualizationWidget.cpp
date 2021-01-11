#include "VisualizationWidget.h"

#include "soccer-common/gui/Widgets/Widgets.h"
#include "soccer-common/gui/MainWindow/MainWindow.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"

void VisualizationWidget::setupVisualizationWidget(MainWindow* mainWindow) {
  m_gameVisualizer = new GameVisualizer(QSizeF(5'000, 5'000), mainWindow);
  mainWindow->visualizationWidget()->layout()->addWidget(m_gameVisualizer);
}

VisualizationWidget::VisualizationWidget() {
}

GameVisualizer* VisualizationWidget::gameVisualizer() {
  return m_gameVisualizer;
}
