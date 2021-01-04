#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <QAction>
#include <QTabWidget>
#include <QElapsedTimer>
#include "soccer-common/Utils/Utils.h"
#include "soccer-common/gui/guiUtils/guiUtils.h"

class MainWindow;
class ScrollAreaForFlowLayout;
class ModuleBox;
class WidgetSettings;
class MenuBarOptions;

namespace Factory {
  QAction* toggleViewAction(const QString& name, QWidget* widget);

  template <class Widget>
  QAction* toggleViewAction(Widget* widget) {
    return toggleViewAction(Utils::nameOfType<Widget>(),
                            static_cast<QWidget*>(widget));
  }

  QAction*
  toggleViewAction(const QString& name, int index, QTabWidget* tabWidget);

  QElapsedTimer startedElapsedTimer();

  ScrollAreaForFlowLayout* scrollAreaWithFlowLayout(QWidget* parent);

  ModuleBox* moduleBox(
      const QString& key,
      MainWindow* mainWindow,
      std::optional<QWidgetWith<WidgetSettings, MenuBarOptions>> optParent =
          std::nullopt);
} // namespace Factory

#endif // GUIFACTORY_H