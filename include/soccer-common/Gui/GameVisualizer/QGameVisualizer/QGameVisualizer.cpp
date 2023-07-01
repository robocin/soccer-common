#include "QGameVisualizer.h"

QGameVisualizer::QGameVisualizer(const QSizeF& defaultSize,
                               QWidgetWith<WidgetSettings, MenuBarOptions> parent,
                               Qt::WindowFlags f): GameVisualizerBase(defaultSize, parent, f), QPainter2DWrapper(){
}

void QGameVisualizer::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QBrush brush;
    setPainter(&painter);
    setBrush(&brush);
    getUpdates();
    /* drawing here. */ {
    for (auto& painting : _local.paintings) {
      for (auto& ptr : painting) {
        if (ptr.second.visibility()) {
          ptr.second->run(static_cast<QPainter2DWrapper*>(this));
        }
      }
    }
  }
}