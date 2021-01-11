#ifndef VISUALIZATIONWIDGET_H
#define VISUALIZATIONWIDGET_H

#include "soccer-common/gui/GameVisualizer/GameVisualizer.h"

class MainWindow;

class VisualizationWidget {
  GameVisualizer* m_gameVisualizer;

 protected:
  void setupVisualizationWidget(MainWindow* mainWindow);

 public:
  explicit VisualizationWidget();
  GameVisualizer* gameVisualizer();
};

#endif // VISUALIZATIONWIDGET_H
