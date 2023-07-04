#include "GameVisualizer.h"
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

GameVisualizer::GameVisualizer(const QSizeF& defaultSize,
                               QWidgetWith<WidgetSettings, MenuBarOptions> parent,
                               Qt::WindowFlags f): GameVisualizerBase(defaultSize, parent, f) {
                                setFormat(this);
}

void GameVisualizer::setFormat(QOpenGLWidget* widget) {
  QSurfaceFormat format;
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setColorSpace(QColorSpace(QColorSpace::SRgb));
  format.setVersion(2, 1);
  widget->setFormat(format);
}

void GameVisualizer::initializeGL() {
  initializeOpenGLFunctions();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LINE_STIPPLE);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  putBackgroundColor(_local.backgroundColor);
}

void GameVisualizer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void GameVisualizer::paintGL() {
  PushPopGuard guard(this);
  getUpdates();
  putBackgroundColor(_local.backgroundColor);
  recomputeProjection();
  prepareToPaint();
  /* drawing here. */ {
    setZ(0);
    for (auto& painting : _local.paintings) {
      for (auto& ptr : painting) {
        if (ptr.second.visibility()) {
          ptr.second->run(static_cast<GameVisualizerPainter2D*>(this));
        }
      }
    }
  }
}

void GameVisualizer::prepareToPaint() {
  glShadeModel(GL_SMOOTH);
  glDisable(GL_LIGHTING);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
}

void GameVisualizer::recomputeProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5 * _local.scale * width() + _local.viewOffset.x(),
          +0.5 * _local.scale * width() + _local.viewOffset.x(),
          -0.5 * _local.scale * height() + _local.viewOffset.y(),
          +0.5 * _local.scale * height() + _local.viewOffset.y(),
          VConst::minZ,
          VConst::maxZ);
  glMatrixMode(GL_MODELVIEW);
}
