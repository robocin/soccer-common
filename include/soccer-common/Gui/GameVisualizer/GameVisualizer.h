#ifndef SOCCER_COMMON_GAMEVISUALIZER_H
#define SOCCER_COMMON_GAMEVISUALIZER_H

#include <QtGui>
#include <QOpenGLWidget>
#include "Painting/Painting.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "GameVisualizerPainter2D/GameVisualizerPainter2D.h"
#include "soccer-common/MagicEnum/MagicEnum.h"

#include "soccer-common/Gui/Interfaces/MenuBarOptions/MenuBarOptions.h"
#include "soccer-common/Gui/Interfaces/WidgetSettings/WidgetSettings.h"

class GameVisualizer : public QOpenGLWidget,
                       protected GameVisualizerPainter2D,
                       public WidgetSettings,
                       public MenuBarOptions {
  Q_OBJECT
 protected:
  void putWidgetActions(MainWindowMenuBar& menubar) override;
  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  class PaintingPointer;

 public:
  explicit GameVisualizer(const QSizeF& defaultSize,
                          QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());

  ~GameVisualizer() override = default;

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
  void clearUniqueIntegerKey(int uniqueKey, Painting::Layers layer);
  void setVisibility(int uniqueKey, bool visibility);
  void setUpdateGL(bool update);

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
      if (static_cast<double>(widget->shared->stopwatch.ref().elapsed()) <
          widget->local.maxFrameRate) {
        return false;
      }
      widget->shared->stopwatch.ref().start();
      return true;
    }

   public:
    Q_DISABLE_COPY_MOVE(ScheduleUpdateAtEnd);

    explicit inline ScheduleUpdateAtEnd(GameVisualizer* t_widget) : widget(t_widget) {
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
    std::array<SharedValue<std::map<int, std::unique_ptr<Painting>>>,
               MagicEnum::count<Painting::Layers>()>
        paintings{};

    SharedValue<QVector<QPair<int, bool>>> visibility{};

    SharedValue<QElapsedTimer> stopwatch = Factory::startedElapsedTimer();

    SharedOptional<int> maxFrameRate;
    SharedOptional<qreal> scale;
    SharedOptional<QColor> backgroundColor;
  };
  SharedWrapper<Shared, std::mutex> shared;

  struct Local {
    std::array<std::map<int, PaintingPointer>, MagicEnum::count<Painting::Layers>()> paintings{};

    qreal maxFrameRate = 1000.0 / 60.0;
    qreal scale = 5'000;
    QColor backgroundColor = Color::Green;

    QPointF mouse = QPointF{0, 0};
    QPointF viewOffset = QPointF{0, 0};
    bool update = true;
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
  explicit PaintingPointer(Args&&... args) :
      std::unique_ptr<Painting>(std::forward<Args>(args)...),
      m_visibility(true) {
  }

  inline void setVisibility(bool visibility) {
    m_visibility = visibility;
  }

  [[nodiscard]] inline bool visibility() const {
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
    m_key = GameVisualizer::getUniqueIntegerKey();
    m_layer = layer;
    //
    QObject::connect(this,
                     &GameVisualizer::Key::onClearKey,
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
                     &GameVisualizer::Key::onPaintingEmitted,
                     gameVisualizer,
                     &GameVisualizer::draw,
                     Qt::DirectConnection);
  }

  inline void draw(Painting&& painting) {
    emit onPaintingEmitted(m_key, painting.clone().release(), m_layer);
  }

  inline void draw(const Painting& painting) {
    emit onPaintingEmitted(m_key, painting.clone().release(), m_layer);
  }

  inline void draw(std::unique_ptr<Painting>&& painting) {
    emit onPaintingEmitted(m_key, painting.release(), m_layer);
  }

  inline void draw(const std::unique_ptr<Painting>& painting) {
    emit onPaintingEmitted(m_key, painting->clone().release(), m_layer);
  }

  template <class Functor>
  inline std::enable_if_t<
      std::is_constructible_v<std::function<void(GameVisualizerPainter2D*)>, Functor>>
  draw(Functor&& functor) {
    emit onPaintingEmitted(m_key,
                           Painting::create(std::forward<Functor>(functor)).release(),
                           m_layer);
  }

  inline void clear() {
    emit onClearKey(m_key, m_layer);
  }

  inline void setVisibility(bool isVisible) {
    emit onVisibilityChanged(m_key, isVisible);
  }

  inline ~Key() override {
    emit onClearKey(m_key, m_layer);
  }

  inline explicit operator int() const {
    return m_key;
  }

 signals:
  void onClearKey(int key, Painting::Layers layer);
  void onVisibilityChanged(int key, bool visibility);
  void onPaintingEmitted(int uniqueIntegerKey, Painting* painting, Painting::Layers layer);

 private:
  int m_key;
  Painting::Layers m_layer;
};

#endif // SOCCER_COMMON_GAMEVISUALIZER_H
