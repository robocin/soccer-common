#ifndef VSS_UNIFICATION_GAMEVISUALIZER_H
#define VSS_UNIFICATION_GAMEVISUALIZER_H

#include <QtGui>
#include <QOpenGLWidget>
#include "GameVisualizerPainter2D/GameVisualizerPainter2D.h"
#include "soccer-common/MagicEnum/MagicEnum.h"
#include "GameVisualizerBase/GameVisualizerBase.h"

class GameVisualizer : public GameVisualizerBase, protected GameVisualizerPainter2D {
public:
  GameVisualizer(const QSizeF& defaultSize,
                          QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());

protected:
  static void setFormat(QOpenGLWidget* widget);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void prepareToPaint();
  void recomputeProjection();
};

#endif // VSS_UNIFICATION_GAMEVISUALIZER_H
