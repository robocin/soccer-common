#ifndef SOCCER_COMMON_SCROLLAREAFORFLOWLAYOUT_H
#define SOCCER_COMMON_SCROLLAREAFORFLOWLAYOUT_H

#include <QtCore>
#include <QtWidgets>

class ScrollAreaForFlowLayout : public QScrollArea {
 public:
  explicit ScrollAreaForFlowLayout(QWidget* parent = nullptr);
  void resizeEvent(QResizeEvent*) override;
};

#endif // SOCCER_COMMON_SCROLLAREAFORFLOWLAYOUT_H
