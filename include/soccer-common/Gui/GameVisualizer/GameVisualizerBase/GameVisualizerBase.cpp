#include "GameVisualizerBase.h"

GameVisualizerBase::GameVisualizerBase(const QSizeF& defaultSize,
                          QWidgetWith<WidgetSettings, MenuBarOptions> parent,
                          Qt::WindowFlags f) :
    QOpenGLWidget(parent, f),
    WidgetSettings(this, parent),
    MenuBarOptions(parent){
    setDefaultSize(defaultSize);

    /* allows mouse */ { setMouseTracking(true); }
    /* allows keyboard */ { setFocusPolicy(Qt::StrongFocus); }
}


void GameVisualizerBase::setBackgroundColor(const QColor& color) {
  ScheduleUpdateAtEnd schedule(this);
  shared->backgroundColor = color;
}

void GameVisualizerBase::setDefaultSize(const QSizeF& size) {
  ScheduleUpdateAtEnd schedule(this);
  shared->scale = std::max(size.width() / width(), size.height() / height());
}

void GameVisualizerBase::setMaxFrameRate(qreal frameRate) {
  shared->maxFrameRate = 1000.0 / frameRate;
}

void GameVisualizerBase::forceDraw() {
  ScheduleUpdateAtEnd schedule(this);
}

void GameVisualizerBase::draw(int uniqueIntegerKey, Painting* painting, Painting::Layers layer) {
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

void GameVisualizerBase::clearUniqueIntegerKey(int uniqueKey, Painting::Layers layer) {
  ScheduleUpdateAtEnd schedule(this);
  int idx = static_cast<int>(layer);
  shared->paintings[idx].apply(
      [uniqueKey](std::map<int, std::unique_ptr<Painting>>& paintings) -> void {
        paintings[uniqueKey] = nullptr;
      });
}

void GameVisualizerBase::setVisibility(int uniqueKey, bool visibility) {
  ScheduleUpdateAtEnd schedule(this);
  shared->visibility->emplace_back(uniqueKey, visibility);
}

void GameVisualizerBase::mousePressEvent(QMouseEvent* event) {
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
    _local.mouse = event->pos();
  } else if (rightButton) {
    auto center = frameGeometry().center();
    _local.viewOffset.rx() += _local.scale * (event->position().x() - center.x());
    _local.viewOffset.ry() -= _local.scale * (event->position().y() - center.y());
  }
}

void GameVisualizerBase::mouseReleaseEvent(QMouseEvent*) {
  ScheduleUpdateAtEnd schedule(this);
  setCursor(Qt::ArrowCursor);
}

void GameVisualizerBase::mouseMoveEvent(QMouseEvent* event) {
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MiddleButton);
  if (leftButton || midButton) {
    ScheduleUpdateAtEnd schedule(this);
    if (leftButton) {
      _local.viewOffset.rx() -= _local.scale * (event->position().x() - _local.mouse.x());
      _local.viewOffset.ry() += _local.scale * (event->position().y() - _local.mouse.y());
    } else {
      qreal zoomRatio = (event->position().y() - _local.mouse.y()) / 500.0;
      _local.scale *= (1.0 + zoomRatio);
    }
    _local.mouse = event->pos();
  }
  auto center = frameGeometry().center();
  auto relativePos = _local.viewOffset;
  relativePos.rx() += _local.scale * (event->position().x() - center.x());
  relativePos.ry() -= _local.scale * (event->position().y() - center.y());
  emit relativeMousePos(relativePos);
}

void GameVisualizerBase::wheelEvent(QWheelEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  qreal zoomRatio = -event->angleDelta().y() / 1000.0;
  _local.scale *= (1.0 + zoomRatio);
}

void GameVisualizerBase::keyPressEvent(QKeyEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  switch (event->key()) {
    case Qt::Key_C: {
      _local.viewOffset = QPoint{0, 0};
      break;
    }
  }
  emit onKeyPress(static_cast<Qt::Key>(event->key()));
}

void GameVisualizerBase::keyReleaseEvent(QKeyEvent* event) {
  emit onKeyRelease(static_cast<Qt::Key>(event->key()));
}

int GameVisualizerBase::getUniqueIntegerKey() {
  static std::atomic<int> key(0);
  return key++;
}

void GameVisualizerBase::getUpdates() {
  shared.apply([this](Shared& object) -> void {
    if (object.maxFrameRate) {
      _local.maxFrameRate = object.maxFrameRate.getAndReset();
    }
    if (object.scale) {
      _local.scale = object.scale.getAndReset();
    }
    if (object.backgroundColor) {
      _local.backgroundColor = object.backgroundColor.getAndReset();
    }
    for (std::size_t i = 0; i < _local.paintings.size(); ++i) {
      auto& paintings = _local.paintings[i];
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
        for (auto& painting : _local.paintings) {
          if (painting.find(key) == painting.end()) {
            painting.insert_or_assign(
                key,
                PaintingPointer(Painting::create([](Painter2DBase*) {
                })));
          }
          painting[key].setVisibility(visibility);
        }
      }
      object.visibility->clear();
    }
  });
}

void GameVisualizerBase::putWidgetActions(MainWindowMenuBar& menubar) {
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

void GameVisualizerBase::writeLocalSettings(QSettings& settings) {
  settings.setValue("backgroundColor", _local.backgroundColor);
}

void GameVisualizerBase::loadLocalSettings(const QSettings& settings) {
  if (settings.contains("backgroundColor")) {
    auto backgroundColor = settings.value("backgroundColor").value<QColor>();
    setBackgroundColor(backgroundColor);
  }
}