#include "DynamicFontSizeQLabel.h"

#include <QDebug>

DynamicFontSizeQLabel::DynamicFontSizeQLabel(const QString& text,
                                             QWidget* parent,
                                             Qt::WindowFlags f) :
    QLabel(text, parent, f),
    ratio(1.0) {
  setAlignment(Qt::AlignCenter);
}

DynamicFontSizeQLabel::DynamicFontSizeQLabel(QWidget* parent, Qt::WindowFlags f) :
    QLabel(parent, f),
    ratio(1.0) {
  setAlignment(Qt::AlignCenter);
}

void DynamicFontSizeQLabel::setRatio(qreal ratioValue) {
  ratio = ratioValue;
}

DynamicFontSizeQLabel::~DynamicFontSizeQLabel() {
}

void DynamicFontSizeQLabel::paintEvent(QPaintEvent* event) {
  QFont newFont = font();
  qreal fontSize =
      std::max<qreal>(minimumFontSize, ratio * getWidgetMaximumFontSize(this, this->text()));

  newFont.setPointSizeF(fontSize);
  setFont(newFont);
  QLabel::paintEvent(event);
}

qreal DynamicFontSizeQLabel::getWidgetMaximumFontSize(QWidget* widget, QString text) {
  QFont font = widget->font();
  const QRect widgetRect = widget->contentsRect();
  const qreal widgetWidth = static_cast<qreal>(widgetRect.width());
  const qreal widgetHeight = static_cast<qreal>(widgetRect.height());

  QRectF newFontSizeRect;
  qreal currentSize = font.pointSizeF();

  qreal step = currentSize / 2.0;

  /* If too small, increase step */
  if (step <= fontPrecision) {
    step = fontPrecision * 4.0;
  }

  qreal lastTestedSize = currentSize;

  qreal currentHeight = 0;
  qreal currentWidth = 0;
  if (text.isEmpty() || widgetWidth < minimumFontSize || widgetHeight < minimumFontSize) {
    return currentSize;
  }

  /* Only stop when step is small enough and new size is smaller than QWidget */
  while ((step > fontPrecision) || (currentHeight > widgetHeight) || (currentWidth > widgetWidth)) {
    /* Keep last tested value */
    lastTestedSize = currentSize;

    /* Test label with its font */
    font.setPointSizeF(currentSize);
    /* Use font metrics to test */
    QFontMetricsF fm(font);

    /* Check if widget is QLabel */
    QLabel* label = qobject_cast<QLabel*>(widget);
    if (label) {
      newFontSizeRect =
          fm.boundingRect(widgetRect,
                          (label->wordWrap() ? Qt::TextWordWrap : 0) | label->alignment(),
                          text);
    } else {
      newFontSizeRect = fm.boundingRect(widgetRect, 0, text);
    }

    currentHeight = newFontSizeRect.height();
    currentWidth = newFontSizeRect.width();

    /* If new font size is too big, decrease it */
    if ((currentHeight > widgetHeight) || (currentWidth > widgetWidth)) {
      // qDebug() << "-- contentsRect()" << label->contentsRect() << "rect"<<
      // label->rect() << " newFontSizeRect" << newFontSizeRect << "Tight" <<
      // text << currentSize;
      currentSize -= step;
      /* if step is small enough, keep it constant, so it converge to biggest
       * font size */
      if (step > fontPrecision) {
        step /= 2.0;
      }
      /* Do not allow negative size */
      if (currentSize <= 0) {
        break;
      }
    }
    /* If new font size is smaller than maximum possible size, increase it */
    else {
      currentSize += step;
    }
  }
  return lastTestedSize;
}
