#include "GameVisualizer.h"
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

GameVisualizer::GameVisualizer(const QSizeF& defaultSize,
                               QWidgetWith<WidgetSettings, MenuBarOptions> parent,
                               Qt::WindowFlags f) :
    QOpenGLWidget(parent, f),
    WidgetSettings(this, parent),
    MenuBarOptions(parent) {
  setFormat(this);
  setDefaultSize(defaultSize);

  /* allows mouse */ { setMouseTracking(true); }
  /* allows keyboard */ { setFocusPolicy(Qt::StrongFocus); }
}

void GameVisualizer::setBackgroundColor(const QColor& color) {
  ScheduleUpdateAtEnd schedule(this);
  shared->backgroundColor = color;
}

void GameVisualizer::setDefaultSize(const QSizeF& size) {
  ScheduleUpdateAtEnd schedule(this);
  shared->scale = std::max(size.width() / width(), size.height() / height());
}

void GameVisualizer::setMaxFrameRate(qreal frameRate) {
  shared->maxFrameRate = 1000.0 / frameRate;
}

void GameVisualizer::forceDraw() {
  ScheduleUpdateAtEnd schedule(this);
}

void GameVisualizer::draw(int uniqueIntegerKey, Painting* painting, Painting::Layers layer) {
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
      [uniqueIntegerKey, painting](std::map<int, std::unique_ptr<Painting>>& paintings) -> void {
        paintings[uniqueIntegerKey] = std::unique_ptr<Painting>(painting);
      });
}

void GameVisualizer::clearUniqueIntegerKey(int uniqueKey, Painting::Layers layer) {
  ScheduleUpdateAtEnd schedule(this);
  int idx = static_cast<int>(layer);
  shared->paintings[idx].apply(
      [uniqueKey](std::map<int, std::unique_ptr<Painting>>& paintings) -> void {
        paintings[uniqueKey] = nullptr;
      });
}

void GameVisualizer::setVisibility(int uniqueKey, bool visibility) {
  ScheduleUpdateAtEnd schedule(this);
  shared->visibility->emplace_back(uniqueKey, visibility);
}

void GameVisualizer::mousePressEvent(QMouseEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MiddleButton);
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
    local.viewOffset.rx() += local.scale * (event->position().x() - center.x());
    local.viewOffset.ry() -= local.scale * (event->position().y() - center.y());
  }
}

void GameVisualizer::mouseReleaseEvent(QMouseEvent*) {
  ScheduleUpdateAtEnd schedule(this);
  setCursor(Qt::ArrowCursor);
}

void GameVisualizer::mouseMoveEvent(QMouseEvent* event) {
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MiddleButton);
  if (leftButton || midButton) {
    ScheduleUpdateAtEnd schedule(this);
    if (leftButton) {
      local.viewOffset.rx() -= local.scale * (event->position().x() - local.mouse.x());
      local.viewOffset.ry() += local.scale * (event->position().y() - local.mouse.y());
    } else {
      qreal zoomRatio = (event->position().y() - local.mouse.y()) / 500.0;
      local.scale *= (1.0 + zoomRatio);
    }
    local.mouse = event->pos();
  }
  auto center = frameGeometry().center();
  auto relativePos = local.viewOffset;
  relativePos.rx() += local.scale * (event->position().x() - center.x());
  relativePos.ry() -= local.scale * (event->position().y() - center.y());
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
    for (auto& painting : local.paintings) {
      for (auto& ptr : painting) {
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
  format.setColorSpace(QColorSpace(QColorSpace::SRgb));
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
  shared.apply([this](Shared& object) -> void {
    if (object.maxFrameRate) {
      local.maxFrameRate = object.maxFrameRate.getAndReset();
    }
    if (object.scale) {
      local.scale = object.scale.getAndReset();
    }
    if (object.backgroundColor) {
      local.backgroundColor = object.backgroundColor.getAndReset();
    }
    for (std::size_t i = 0; i < local.paintings.size(); ++i) {
      auto& paintings = local.paintings[i];
      for (auto& ptr : object.paintings[i].ref()) {
        if (ptr.second) {
          bool visibility =
              (paintings.find(ptr.first) == paintings.end()) || paintings[ptr.first].visibility();
          auto it =
              paintings
                  .insert_or_assign(ptr.first, static_cast<PaintingPointer>(std::move(ptr.second)))
                  .first;
          it->second.setVisibility(visibility);
        } else {
          paintings.erase(ptr.first);
        }
      }
      object.paintings[i].ref().clear();
    }
    {
      for (auto [key, visibility] : object.visibility.ref()) {
        for (auto& painting : local.paintings) {
          if (painting.find(key) == painting.end()) {
            painting.insert_or_assign(
                key,
                PaintingPointer(Painting::create([](GameVisualizerPainter2D*) {
                })));
          }
          painting[key].setVisibility(visibility);
        }
      }
      object.visibility->clear();
    }
  });
}

void GameVisualizer::putWidgetActions(MainWindowMenuBar& menubar) {
  /* open config */ {
    auto* changeBackgroundColor = new QAction("Background Color...", &menubar["Visualization"]);
    QObject::connect(changeBackgroundColor, &QAction::triggered, this, [this]() {
      QColor color = QColorDialog::getColor(Color::Green, this, "Background Color:");
      if (color.isValid()) {
        setBackgroundColor(color);
      }
    });
    menubar["Visualization"].addAction(changeBackgroundColor);
  }
}

void GameVisualizer::writeLocalSettings(QSettings& settings) {
  settings.setValue("backgroundColor", local.backgroundColor);
}

void GameVisualizer::loadLocalSettings(const QSettings& settings) {
  if (settings.contains("backgroundColor")) {
    auto backgroundColor = settings.value("backgroundColor").value<QColor>();
    setBackgroundColor(backgroundColor);
  }
}
