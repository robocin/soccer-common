#ifndef SOCCER_COMMON_GUIFACTORY_H
#define SOCCER_COMMON_GUIFACTORY_H

#include <QAction>
#include <QTabWidget>
#include <QElapsedTimer>
#include "soccer-common/Utils/Utils.h"
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"

class MainWindow;
class ScrollAreaForFlowLayout;
class ModuleBox;
class WidgetSettings;
class MenuBarOptions;

namespace Factory {
  QAction* toggleViewAction(const QString& name, QWidget* widget);

  template <class Widget>
  QAction* toggleViewAction(Widget* widget) {
    return toggleViewAction(Utils::nameOfType<Widget>(), static_cast<QWidget*>(widget));
  }

  QAction* toggleViewAction(const QString& name, int index, QTabWidget* tabWidget);

  QElapsedTimer startedElapsedTimer();

  ScrollAreaForFlowLayout* scrollAreaWithFlowLayout(QWidget* parent);

  ModuleBox*
  moduleBox(const QString& key,
            MainWindow* mainWindow,
            std::optional<QWidgetWith<WidgetSettings, MenuBarOptions>> optParent = std::nullopt);
} // namespace Factory

#endif // SOCCER_COMMON_GUIFACTORY_H
