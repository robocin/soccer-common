#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QtGui>
#include <QOpenGLWidget>
#include "Painting/Painting.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "GameVisualizerPainter2D/GameVisualizerPainter2D.h"
#include "soccer-common/MagicEnum/MagicEnum.h"

class GameVisualizer : public QOpenGLWidget, protected GameVisualizerPainter2D {
  Q_OBJECT

  class PaintingPointer;

 public:
  explicit GameVisualizer(const QSizeF& defaultSize,
                          QWidget* parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());

  ~GameVisualizer() override;

  class Key;

 signals:
  void relativeMousePos(const QPointF& position);
  void onKeyPress(Qt::Key key);
  void onKeyRelease(Qt::Key key);

 public slots:
  void setBackgroundColor(const QColor& color);
  void setDefaultSize(const QSizeF& size);
  void setMaxFrameRate(qreal frameRate);

  void forceDraw();

 private slots:
  void draw(int uniqueIntegerKey, Painting* painting, Painting::Layers layer);
  void clearUniqueIntegerKey(int uniqueKey);
  void setVisibility(int uniqueKey, bool visibility);

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  static void setFormat(QOpenGLWidget* widget);
  static int getUniqueIntegerKey();

  void prepareToPaint();
  void recomputeProjection();

  class ScheduleUpdateAtEnd {
    GameVisualizer* widget;

    bool canUpdate() {
      if (widget->shared->stopwatch.ref().elapsed() <
          widget->local.maxFrameRate) {
        return false;
      }
      widget->shared->stopwatch.ref().start();
      return true;
    }

   public:
    Q_DISABLE_COPY_MOVE(ScheduleUpdateAtEnd);

    explicit inline ScheduleUpdateAtEnd(GameVisualizer* t_widget) :
        widget(t_widget) {
      Q_ASSERT(t_widget != nullptr);
    }
    inline ~ScheduleUpdateAtEnd() {
      if (canUpdate()) {
        QMetaObject::invokeMethod(widget,
                                  qOverload<>(&GameVisualizer::update),
                                  Qt::QueuedConnection);
      }
    }
  };

  struct Shared {
    std::array<SetterGetter<std::map<int, std::unique_ptr<Painting>>>,
               MagicEnum::count<Painting::Layers>()>
        paintings{};

    SetterGetter<QVector<QPair<int, bool>>> visibility{};

    SetterGetter<QElapsedTimer> stopwatch = Factory::startedElapsedTimer();

    SharedOptional<int> maxFrameRate;
    SharedOptional<qreal> scale;
    SharedOptional<QColor> backgroundColor;
  };
  SharedWrapper<Shared, std::mutex> shared;

  struct Local {
    std::array<std::map<int, PaintingPointer>,
               MagicEnum::count<Painting::Layers>()>
        paintings{};

    qreal maxFrameRate = 1000.0 / 60.0;
    qreal scale = 5'000;
    QColor backgroundColor = Color::Green;

    QPointF mouse = QPointF{0, 0};
    QPointF viewOffset = QPointF{0, 0};
  };
  Local local;

  void getUpdates();

  struct Const {
    static constexpr int minZ = -100;
    static constexpr int maxZ = +100;
  };
};

class GameVisualizer::PaintingPointer : public std::unique_ptr<Painting> {
  bool m_visibility;

 public:
  template <class... Args>
  PaintingPointer(Args&&... args) :
      std::unique_ptr<Painting>(std::forward<Args>(args)...),
      m_visibility(true) {
  }

  inline void setVisibility(bool visibility) {
    m_visibility = visibility;
  }

  inline bool visibility() const {
    return m_visibility;
  }
};

class GameVisualizer::Key : public QObject {
  Q_OBJECT

 public:
  Q_DISABLE_COPY_MOVE(Key);

  inline Key() : m_key(-1), m_layer(Painting::Layers::Middle) {
  }

  inline void setup(GameVisualizer* gameVisualizer,
                    Painting::Layers layer = Painting::Layers::Middle) {
    if (m_key != -1) {
      qWarning() << "cannot setup twice.";
      return;
    }
    m_key = gameVisualizer->getUniqueIntegerKey();
    m_layer = layer;
    //
    QObject::connect(this,
                     &GameVisualizer::Key::onKeyDeleted,
                     gameVisualizer,
                     &GameVisualizer::clearUniqueIntegerKey,
                     Qt::QueuedConnection);
    //
    QObject::connect(this,
                     &GameVisualizer::Key::onVisibilityChanged,
                     gameVisualizer,
                     &GameVisualizer::setVisibility,
                     Qt::QueuedConnection);
    //
    QObject::connect(this,
                     &GameVisualizer::Key::onPaintingEmmited,
                     gameVisualizer,
                     &GameVisualizer::draw,
                     Qt::DirectConnection);
  }

  inline void draw(const Painting& painting) {
    emit onPaintingEmmited(m_key, painting.clone().release(), m_layer);
  }

  inline void draw(std::unique_ptr<Painting> painting) {
    emit onPaintingEmmited(m_key, painting.release(), m_layer);
  }

  inline void draw(std::unique_ptr<Painting>& painting) {
    emit onPaintingEmmited(m_key, painting->clone().release(), m_layer);
  }

  inline void setVisibility(bool visibility) {
    emit onVisibilityChanged(m_key, visibility);
  }

  inline ~Key() {
    emit onKeyDeleted(m_key);
  }

  inline operator int() const {
    return m_key;
  }

 signals:
  void onKeyDeleted(int key);
  void onVisibilityChanged(int key, bool visibility);
  void onPaintingEmmited(int uniqueIntegerKey,
                         Painting* painting,
                         Painting::Layers layer);

 private:
  int m_key;
  Painting::Layers m_layer;
};

#endif // GAMEVISUALIZER_H
