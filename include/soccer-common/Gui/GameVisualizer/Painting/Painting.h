#ifndef SOCCER_COMMON_PAINTING_H
#define SOCCER_COMMON_PAINTING_H

#include <memory>
#include <functional>

class GameVisualizerPainter2D;

class Painting {
  class FunctionPainting;

 public:
  enum class Layers;

  Painting() = default;
  virtual ~Painting() = default;
  virtual void run(GameVisualizerPainter2D* f) = 0;
  virtual std::unique_ptr<Painting> clone() const = 0;

  template <class F>
  static std::unique_ptr<Painting> create(F&& function);
};

enum class Painting::Layers : int { Bottom, AboveBottom, Middle, AboveMiddle, Top };

class Painting::FunctionPainting : public Painting {
  std::function<void(GameVisualizerPainter2D*)> m_function;

 public:
  template <class F>
  inline explicit FunctionPainting(F function) : m_function(std::move(function)) {
  }

  inline void run(GameVisualizerPainter2D* f) override {
    m_function(f);
  }

  inline std::unique_ptr<Painting> clone() const override {
    return std::make_unique<FunctionPainting>(*this);
  }
};

template <class F>
inline std::unique_ptr<Painting> Painting::create(F&& function) {
  return std::make_unique<FunctionPainting>(std::forward<F>(function));
}

#endif // SOCCER_COMMON_PAINTING_H
