#ifndef VISUALIZATIONWIDGET_H
#define VISUALIZATIONWIDGET_H

#include <QSizeF>
#include "soccer-common/gui/GameVisualizer/GameVisualizer.h"

class MainWindow;

class VisualizationWidget {
  QSizeF m_defaultSize;
  GameVisualizer* m_gameVisualizer;

 protected:
  void setupVisualizationWidget(MainWindow* mainWindow);

 public:
  explicit VisualizationWidget(const QSizeF& defaultSize);
  GameVisualizer* gameVisualizer();
};

#endif // VISUALIZATIONWIDGET_H
