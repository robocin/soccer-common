#ifndef SOCCER_COMMON_VISUALIZATIONWIDGET_H
#define SOCCER_COMMON_VISUALIZATIONWIDGET_H

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

#endif // SOCCER_COMMON_VISUALIZATIONWIDGET_H
