#ifndef VSS_UNIFICATION_QGAMEVISUALIZER_H
#define VSS_UNIFICATION_QGAMEVISUALIZER_H

#include "soccer-common/Gui/GameVisualizer/GameVisualizerBase/GameVisualizerBase.h"
#include "soccer-common/Gui/GameVisualizer/QPainter2DWrapper/QPainter2DWrapper.h"

class QGameVisualizer : public GameVisualizerBase, protected QPainter2DWrapper {
public:
    QGameVisualizer(const QSizeF& defaultSize,
                          QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};

#endif // VSS_UNIFICATION_QGAMEVISUALIZER_H
