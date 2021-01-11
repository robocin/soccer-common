#include "GameVisualizer.h"

GameVisualizer::GameVisualizer(const QSizeF& defaultSize,
                               QWidget* parent,
                               Qt::WindowFlags f) :
    QOpenGLWidget(parent, f) {
  setFormat(this);
  setDefaultSize(defaultSize);

  /* allows mouse */ { setMouseTracking(true); }
  /* allows keyboard */ { setFocusPolicy(Qt::StrongFocus); }
}

GameVisualizer::~GameVisualizer() {
}

void GameVisualizer::setBackgroundColor(QColor color) {
  ScheduleUpdateAtEnd schedule(this);
  shared->backgroundColor = color;
}

void GameVisualizer::setDefaultSize(QSizeF size) {
  ScheduleUpdateAtEnd schedule(this);
  shared->scale = std::max(size.width() / width(), size.height() / height());
}

void GameVisualizer::setMaxFrameRate(qreal frameRate) {
  shared->maxFrameRate = 1000.0 / frameRate;
}

void GameVisualizer::forceDraw() {
  ScheduleUpdateAtEnd schedule(this);
}

void GameVisualizer::draw(int uniqueIntegerKey,
                          Painting* painting,
                          Painting::Layers layer) {
  ScheduleUpdateAtEnd schedule(this);
  if (uniqueIntegerKey < 0) {
    qWarning() << "the key was not initialized.";
    return;
  }
  if (!painting) {
    qWarning() << "painting is null.";
    return;
  }
  int idx = static_cast<int>(layer);
  shared->paintings[idx].apply(
      [uniqueIntegerKey,
       painting](std::map<int, std::unique_ptr<Painting>>& paintings) -> void {
        paintings[uniqueIntegerKey] = painting->clone();
      });
}

void GameVisualizer::clearUniqueIntegerKey(int uniqueKey) {
  ScheduleUpdateAtEnd schedule(this);
  for (int i = 0; i < MagicEnum::count<Painting::Layers>(); ++i) {
    shared->paintings[i].apply(
        [uniqueKey](
            std::map<int, std::unique_ptr<Painting>>& paintings) -> void {
          if (paintings.find(uniqueKey) != paintings.end()) {
            paintings[uniqueKey] = nullptr;
          }
        });
  }
}

void GameVisualizer::setVisibility(int uniqueKey, bool visibility) {
  ScheduleUpdateAtEnd schedule(this);
  shared->visibility->append(QPair(uniqueKey, visibility));
}

void GameVisualizer::mousePressEvent(QMouseEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MidButton);
  bool rightButton = event->buttons().testFlag(Qt::RightButton);

  if (leftButton || midButton) {
    if (leftButton) {
      setCursor(Qt::ClosedHandCursor);
    }
    if (midButton) {
      setCursor(Qt::SizeVerCursor);
    }
    local.mouse = event->pos();
  } else if (rightButton) {
    auto center = frameGeometry().center();
    local.viewOffset.rx() += local.scale * (event->x() - center.x());
    local.viewOffset.ry() -= local.scale * (event->y() - center.y());
  }
}

void GameVisualizer::mouseReleaseEvent(QMouseEvent*) {
  ScheduleUpdateAtEnd schedule(this);
  setCursor(Qt::ArrowCursor);
}

void GameVisualizer::mouseMoveEvent(QMouseEvent* event) {
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MidButton);
  if (leftButton || midButton) {
    ScheduleUpdateAtEnd schedule(this);
    if (leftButton) {
      local.viewOffset.rx() -= local.scale * (event->x() - local.mouse.x());
      local.viewOffset.ry() += local.scale * (event->y() - local.mouse.y());
    } else if (midButton) {
      qreal zoomRatio = (event->y() - local.mouse.y()) / 500.0;
      local.scale *= (1.0 + zoomRatio);
    }
    local.mouse = event->pos();
  }
  auto center = frameGeometry().center();
  auto relativePos = local.viewOffset;
  relativePos.rx() += local.scale * (event->x() - center.x());
  relativePos.ry() -= local.scale * (event->y() - center.y());
  emit relativeMousePos(relativePos);
}

void GameVisualizer::wheelEvent(QWheelEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  qreal zoomRatio = -event->angleDelta().y() / 1000.0;
  local.scale *= (1.0 + zoomRatio);
}

void GameVisualizer::keyPressEvent(QKeyEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  switch (event->key()) {
    case Qt::Key_C: {
      local.viewOffset = QPoint{0, 0};
      break;
    }
  }
  emit onKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameVisualizer::keyReleaseEvent(QKeyEvent* event) {
  emit onKeyRelease(static_cast<Qt::Key>(event->key()));
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

  putBackgroundColor(local.backgroundColor);
}

void GameVisualizer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void GameVisualizer::paintGL() {
  PushPopGuard guard(this);
  getUpdates();
  putBackgroundColor(local.backgroundColor);
  recomputeProjection();
  prepareToPaint();
  /* drawing here. */ {
    setZ(0);
    for (std::size_t i = 0; i < local.paintings.size(); ++i) {
      for (auto& ptr : local.paintings[i]) {
        if (ptr.second.visibility()) {
          ptr.second->run(static_cast<GameVisualizerPainter2D*>(this));
        }
      }
    }
  }
}

void GameVisualizer::setFormat(QOpenGLWidget* widget) {
  QSurfaceFormat format;
  format.setProfile(QSurfaceFormat::CompatibilityProfile);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  format.setColorSpace(QSurfaceFormat::DefaultColorSpace);
  format.setVersion(2, 1);
  widget->setFormat(format);
}

int GameVisualizer::getUniqueIntegerKey() {
  static std::atomic<int> key(0);
  return key++;
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
  glOrtho(-0.5 * local.scale * width() + local.viewOffset.x(),
          +0.5 * local.scale * width() + local.viewOffset.x(),
          -0.5 * local.scale * height() + local.viewOffset.y(),
          +0.5 * local.scale * height() + local.viewOffset.y(),
          Const::minZ,
          Const::maxZ);
  glMatrixMode(GL_MODELVIEW);
}

void GameVisualizer::getUpdates() {
  shared.apply([this](Shared& shared) -> void {
    if (shared.maxFrameRate) {
      local.maxFrameRate = shared.maxFrameRate.getAndReset();
    }
    if (shared.scale) {
      local.scale = shared.scale.getAndReset();
    }
    if (shared.backgroundColor) {
      local.backgroundColor = shared.backgroundColor.getAndReset();
    }
    for (std::size_t i = 0; i < local.paintings.size(); ++i) {
      for (auto& ptr : shared.paintings[i].ref()) {
        if (ptr.second) {
          local.paintings[i][ptr.first] = std::move(ptr.second);
        } else {
          local.paintings[i].erase(ptr.first);
        }
      }
      shared.paintings[i].ref().clear();
    }
    {
      for (auto [key, visibility] : shared.visibility.ref()) {
        for (std::size_t i = 0; i < local.paintings.size(); ++i) {
          if (local.paintings[i].find(key) != local.paintings[i].end()) {
            local.paintings[i][key].setVisibility(visibility);
          }
        }
      }
      shared.visibility->clear();
    }
  });
}
