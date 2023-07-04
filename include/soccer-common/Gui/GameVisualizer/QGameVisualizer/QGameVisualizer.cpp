#include "QGameVisualizer.h"

QGameVisualizer::QGameVisualizer(const QSizeF& defaultSize,
                               QWidgetWith<WidgetSettings, MenuBarOptions> parent,
                               Qt::WindowFlags f): GameVisualizerBase(defaultSize, parent, f), QPainter2DWrapper(){
}

void QGameVisualizer::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    setPainter(&painter);
    QBrush brush;
    brush.setColor(_local.backgroundColor);
    painter.fillRect(event->rect(), _local.backgroundColor);
    getUpdates();
    painter.save();
    // painter.rotate(180);
    painter.scale(-_local.scale, -_local.scale);
    painter.translate(_local.viewOffset);
    /* drawing here. */ {
    for (auto& painting : _local.paintings) {
      for (auto& ptr : painting) {
        if (ptr.second.visibility()) {
          ptr.second->run(static_cast<QPainter2DWrapper*>(this));
        }
      }
    }
    painter.restore();
    painter.end();
  }
}

void QGameVisualizer::mousePressEvent(QMouseEvent* event) {
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

void QGameVisualizer::mouseMoveEvent(QMouseEvent* event) {
  bool leftButton = event->buttons().testFlag(Qt::LeftButton);
  bool midButton = event->buttons().testFlag(Qt::MiddleButton);
  if (leftButton || midButton) {
    ScheduleUpdateAtEnd schedule(this);
    if (leftButton) {
      _local.viewOffset.rx() -= _local.scale * (event->position().x() - _local.mouse.x());
      _local.viewOffset.ry() -= _local.scale * (event->position().y() - _local.mouse.y());
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

void QGameVisualizer::wheelEvent(QWheelEvent* event) {
  ScheduleUpdateAtEnd schedule(this);
  qreal zoomRatio = event->angleDelta().y() / 1000.0;
  _local.scale *= (1.0 + zoomRatio);
}