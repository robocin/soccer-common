#ifndef SOCCER_COMMON_VISUALIZATIONWIDGET_H
#define SOCCER_COMMON_VISUALIZATIONWIDGET_H

#include <QSizeF>
#include "soccer-common/Gui/GameVisualizer/GameVisualizerBase/GameVisualizerBase.h"
#include "soccer-common/Gui/GameVisualizer/QGameVisualizer/QGameVisualizer.h"

class MainWindow;

class VisualizationWidget {
  QSizeF m_defaultSize;
  GameVisualizerBase* m_gameVisualizer{};

 protected:
  void setupVisualizationWidget(MainWindow* mainWindow);

 public:
  explicit VisualizationWidget(const QSizeF& defaultSize);
  GameVisualizerBase* gameVisualizer();
};

#endif // SOCCER_COMMON_VISUALIZATIONWIDGET_H
