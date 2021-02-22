#include "GuiFactory.h"
#include "soccer-common/Gui/Widgets/Widgets.h"
#include "soccer-common/Gui/MainWindow/MainWindow.h"

namespace Factory {
  QAction* toggleViewAction(const QString& name, QWidget* widget) {
    auto* action = new QAction(widget);
    action->setText(name);
    action->setCheckable(true);
    action->setChecked(not widget->isVisible());
    QObject::connect(action, &QAction::toggled, widget, [widget](bool checked) {
      checked ? widget->show() : widget->hide();
    });
    return action;
  }

  QAction* toggleViewAction(const QString& name, int index, QTabWidget* tabWidget) {
    auto* action = new QAction(tabWidget);
    action->setText(name);
    action->setCheckable(true);
    action->setChecked(not tabWidget->tabBar()->isTabVisible(index));
    QObject::connect(action, &QAction::toggled, tabWidget, [index, tabWidget](bool checked) {
      tabWidget->tabBar()->setTabVisible(index, checked);
    });
    return action;
  }

  QElapsedTimer startedElapsedTimer() {
    QElapsedTimer et;
    et.start();
    return et;
  }

  ScrollAreaForFlowLayout* scrollAreaWithFlowLayout(QWidget* parent) {
    auto* scrollArea = new ScrollAreaForFlowLayout(parent);
    auto* layout = new SmartVerticalFlowLayout(scrollArea);
    scrollArea->setWidget(new QWidget(scrollArea));
    scrollArea->widget()->setLayout(layout);
    return scrollArea;
  }

  ModuleBox* moduleBox(const QString& key,
                       MainWindow* mainWindow,
                       std::optional<QWidgetWith<WidgetSettings, MenuBarOptions>> optParent) {
    auto parent = optParent.value_or(mainWindow);
    auto moduleBox = new ModuleBox(key, parent);
    auto playPauseButton = mainWindow->playPauseButton();
    QObject::connect(playPauseButton,
                     &PlayPauseWidget::onPushButtonClicked,
                     moduleBox,
                     [moduleBox](bool clicked) {
                       moduleBox->setComboBoxEnabled(!clicked);
                     });
    return moduleBox;
  }
} // namespace Factory
