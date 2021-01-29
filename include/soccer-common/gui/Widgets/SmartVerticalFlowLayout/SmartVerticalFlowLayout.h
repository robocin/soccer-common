#ifndef SOCCER_COMMON_SMARTVERTICALFLOWLAYOUT_H
#define SOCCER_COMMON_SMARTVERTICALFLOWLAYOUT_H

#include <QLayout>
#include <QRect>
#include <QStyle>

QT_BEGIN_NAMESPACE

/**
 * @brief The SmartVerticalFlowLayout class is a flow layout. It provide also
 * standard alignment on item (Left, Center and Right), and can strecth items
 * on the row, in order to use row width entirely (Justify or 0).
 */
class Q_WIDGETS_EXPORT SmartVerticalFlowLayout : public QLayout {
  Q_OBJECT

  Q_PROPERTY(
      int horizontalSpacing READ horizontalSpacing WRITE setHorizontalSpacing)
  Q_PROPERTY(int verticalSpacing READ verticalSpacing WRITE setVerticalSpacing)
  Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
  Q_PROPERTY(int maxRowCount READ maxRowCount WRITE setMaxRowCount)

 public:
  explicit SmartVerticalFlowLayout(QWidget* parent = 0);
  ~SmartVerticalFlowLayout();

  int count() const;
  void addItem(QLayoutItem* item);
  QLayoutItem* itemAt(int index) const;
  QLayoutItem* takeAt(int index);

  int horizontalSpacing() const;
  int verticalSpacing() const;

  int maxRowCount() const;

  /**
   * @brief Return with no expanding direction if aligment isn't justify nor 0.
   * @return Qt::Horizontal or 0
   */
  Qt::Orientations expandingDirections() const;

  QSize sizeHint() const;
  QSize minimumSize() const;
  void setGeometry(const QRect& rect);

 public slots:
  void setHorizontalSpacing(int space);
  void setVerticalSpacing(int space);

  void setMaxRowCount(int count);

  /**
   * @brief Change alignment of all items.
   * You must call SmartVerticalFlowLayout::updateLayout() if called as
   * QLayout* or QLayoutItem* because the function isn't virtual
   *
   * @param align Items alignment (0, Justify, Left, Center, Right)
   */
  void setAlignment(Qt::Alignment align);

  /**
   * @brief Force layout to reprocess all items positions.
   */
  void updateLayout();

 private:
  void doLayout(const QRect& rect);
  int smartSpacing(QStyle::PixelMetric pm) const;

 private:
  QList<QLayoutItem*> m_items;
  int m_hSpace;
  int m_vSpace;

  int m_maxRowCount;

  QRect m_structureGeometry;
  bool m_isLayoutModified;

 private:
  Q_DISABLE_COPY(SmartVerticalFlowLayout)
};

QT_END_NAMESPACE

#endif // SOCCER_COMMON_SMARTVERTICALFLOWLAYOUT_H
