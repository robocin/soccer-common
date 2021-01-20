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
  void connectWithToggleViewAction(QAction* action, QWidget* widget);
  QAction* toggleViewAction(const QString& name, QWidget* parent);
  QAction* toggleViewActionAndConnect(const QString& name, QWidget* widget);

  template <class Widget>
  QAction* toggleViewActionAndConnect(Widget* widget) {
    return toggleViewActionAndConnect(Utils::nameOfType<Widget>(),
                                      static_cast<QWidget*>(widget));
  }

  QAction* toggleViewActionAndConnect(const QString& name,
                                      int index,
                                      QTabWidget* tabWidget);

  QElapsedTimer startedElapsedTimer();

  ScrollAreaForFlowLayout* scrollAreaWithFlowLayout(QWidget* parent);

  ModuleBox* moduleBox(
      const QString& key,
      MainWindow* mainWindow,
      std::optional<QWidgetWith<WidgetSettings, MenuBarOptions>> optParent =
          std::nullopt);
} // namespace Factory

#endif // GUIFACTORY_H
