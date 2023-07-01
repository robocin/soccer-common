#include "VisualizationWidget.h"

#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

void VisualizationWidget::setupVisualizationWidget(MainWindow* mainWindow) {
  m_gameVisualizer = new QGameVisualizer(m_defaultSize, mainWindow);
  mainWindow->visualizationWidget()->layout()->addWidget(m_gameVisualizer);
}

VisualizationWidget::VisualizationWidget(const QSizeF& defaultSize) : m_defaultSize(defaultSize) {
}

GameVisualizerBase* VisualizationWidget::gameVisualizer() {
  return m_gameVisualizer;
}
