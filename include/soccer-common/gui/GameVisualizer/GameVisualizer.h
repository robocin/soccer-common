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

 public:
  explicit GameVisualizer(const QSizeF& defaultSize,
                          QWidget* parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());

  ~GameVisualizer() override;

  class Key;
  Key getUniqueKey() const;

 signals:
  void relativeMousePos(const QPointF& position);
  void onKeyPress(Qt::Key key);
  void onKeyRelease(Qt::Key key);

 public slots:
  void setBackgroundColor(QColor color);
  void setDefaultSize(QSizeF size);
  void setMaxFrameRate(qreal frameRate);

  void forceDraw();
  void draw(int uniqueIntegerKey, Painting* painting, Painting::Layers layer);

 private slots:
  void clearUniqueIntegerKey(int uniqueKey);

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
    SetterGetter<QElapsedTimer> stopwatch = Factory::startedElapsedTimer();

    SharedOptional<int> maxFrameRate;
    SharedOptional<qreal> scale;
    SharedOptional<QColor> backgroundColor;
  };
  SharedWrapper<Shared, QMutex> shared;

  struct Local {
    std::array<std::map<int, std::unique_ptr<Painting>>,
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

class GameVisualizer::Key : public QObject {
  Q_OBJECT
 public:
  Q_DISABLE_COPY_MOVE(Key);

  inline Key() : m_key(-1) {
  }
  inline Key(const GameVisualizer* gameVisualizer) : Key() {
    setup(gameVisualizer);
  }

  inline void setup(const GameVisualizer* gameVisualizer) {
    if (m_key != -1) {
      qWarning() << "cannot setup twice.";
      return;
    }
    m_key = gameVisualizer->getUniqueIntegerKey();
    QObject::connect(this,
                     &GameVisualizer::Key::onKeyDeleted,
                     gameVisualizer,
                     &GameVisualizer::clearUniqueIntegerKey);
  }

  inline ~Key() {
    emit onKeyDeleted(m_key);
  }

  inline operator int() const {
    return m_key;
  }

 signals:
  void onKeyDeleted(int key);

 private:
  int m_key;
};

#endif // GAMEVISUALIZER_H
