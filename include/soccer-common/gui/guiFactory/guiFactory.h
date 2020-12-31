#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <QAction>
#include <QElapsedTimer>
#include "soccer-common/Utils/Utils.h"

class MainWindow;
class ScrollAreaForFlowLayout;

namespace Factory {
  QAction* toggleViewAction(const QString& name, QWidget* widget);

  template <class Widget>
  QAction* toggleViewAction(Widget* widget) {
    return toggleViewAction(Utils::nameOfType<Widget>(),
                            static_cast<QWidget*>(widget));
  }

  QElapsedTimer startedElapsedTimer();

  ScrollAreaForFlowLayout* scrollAreaForFlowLayout(QWidget* widget);
} // namespace Factory

#endif // GUIFACTORY_H
