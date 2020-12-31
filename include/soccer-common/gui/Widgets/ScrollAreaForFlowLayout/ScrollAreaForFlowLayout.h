#ifndef SCROLLAREAFORFLOWLAYOUT_H
#define SCROLLAREAFORFLOWLAYOUT_H

#include <QtCore>
#include <QtWidgets>

class ScrollAreaForFlowLayout : public QScrollArea {
 public:
  explicit ScrollAreaForFlowLayout(QWidget* parent = nullptr);
  void resizeEvent(QResizeEvent*) override;
};

#endif // SCROLLAREAFORFLOWLAYOUT_H
