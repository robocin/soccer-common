#include "guiFactory.h"
#include "soccer-common/gui/Widgets/Widgets.h"

namespace Factory {
  QElapsedTimer startedElapsedTimer() {
    QElapsedTimer et;
    et.start();
    return et;
  }

  ScrollAreaForFlowLayout* scrollAreaForFlowLayout(QWidget* widget) {
    ScrollAreaForFlowLayout* scrollArea = new ScrollAreaForFlowLayout(widget);
    SmartVerticalFlowLayout* layout = new SmartVerticalFlowLayout(scrollArea);
    scrollArea->setWidget(new QWidget(scrollArea));
    scrollArea->widget()->setLayout(layout);
    return scrollArea;
  }

  QAction* toggleViewAction(const QString& name, QWidget* widget) {
    QAction* action = new QAction(widget);
    action->setText(name);
    action->setCheckable(true);
    action->setChecked(not widget->isVisible());
    QObject::connect(action, &QAction::toggled, widget, [widget](bool checked) {
      checked ? widget->show() : widget->hide();
    });
    return action;
  }

} // namespace Factory
