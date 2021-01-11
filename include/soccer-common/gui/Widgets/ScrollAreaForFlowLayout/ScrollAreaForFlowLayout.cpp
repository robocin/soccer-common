#include "ScrollAreaForFlowLayout.h"

ScrollAreaForFlowLayout::ScrollAreaForFlowLayout(QWidget* parent) :
    QScrollArea(parent) {
  setWidgetResizable(true);
  setContentsMargins(-1, -1, -1, -1);
}

void ScrollAreaForFlowLayout::resizeEvent(QResizeEvent*) {
  int w = qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
  if (widget()) {
    if (widget()->layout()) {
      int ax;
      int ay;
      int aw;
      int ah;
      geometry().getRect(&ax, &ay, &aw, &ah);
      widget()->setGeometry(
          QRect(ax, ay, std::max(0, aw - (w + 1)), std::max(0, ah - (w + 1))));
    }
  }
}
