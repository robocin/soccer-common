#ifndef SOCCER_COMMON_DYNAMICFONTSIZEQLABEL_H
#define SOCCER_COMMON_DYNAMICFONTSIZEQLABEL_H

#include <QLabel>
#include <QColor>

class DynamicFontSizeQLabel : public QLabel {
  Q_OBJECT

  qreal ratio;
  static constexpr qreal fontPrecision = 0.5;
  static constexpr qreal minimumFontSize = 11.0;

 public:
  explicit DynamicFontSizeQLabel(const QString& text,
                                 QWidget* parent = nullptr,
                                 Qt::WindowFlags f = Qt::WindowFlags());

  explicit DynamicFontSizeQLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

  void setRatio(qreal ratioValue);

  ~DynamicFontSizeQLabel();

 protected:
  static qreal getWidgetMaximumFontSize(QWidget* widget, QString text);
  void paintEvent(QPaintEvent* event) override;
};

#endif // SOCCER_COMMON_DYNAMICFONTSIZEQLABEL_H
