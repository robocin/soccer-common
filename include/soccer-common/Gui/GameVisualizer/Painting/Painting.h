#ifndef SOCCER_COMMON_PAINTING_H
#define SOCCER_COMMON_PAINTING_H

#include <memory>
#include <functional>

class GameVisualizerPainter2D;

class Painting {
  class FunctionPainting;

 public:
  enum class Layers;

  Painting();
  virtual ~Painting();
  virtual void run(GameVisualizerPainter2D* f) = 0;
  virtual std::unique_ptr<Painting> clone() const = 0;

  static std::unique_ptr<Painting>
  create(std::function<void(GameVisualizerPainter2D*)> function);
};

enum class Painting::Layers : int {
  Bottom,
  AboveBottom,
  Middle,
  AboveMiddle,
  Top
};

class Painting::FunctionPainting : public Painting {
  std::function<void(GameVisualizerPainter2D*)> m_function;

 public:
  inline FunctionPainting(
      std::function<void(GameVisualizerPainter2D*)> function) :
      m_function(std::move(function)) {
  }

  inline void run(GameVisualizerPainter2D* f) override {
    m_function(f);
  }

  inline std::unique_ptr<Painting> clone() const override {
    return std::make_unique<FunctionPainting>(*this);
  }
};

inline std::unique_ptr<Painting>
Painting::create(std::function<void(GameVisualizerPainter2D*)> function) {
  return std::make_unique<Painting::FunctionPainting>(function);
}

#endif // SOCCER_COMMON_PAINTING_H
