#ifndef SOCCER_COMMON_ATTACKSIDEWIDGET_H
#define SOCCER_COMMON_ATTACKSIDEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class AttackSideWidget;
}

class AttackSideWidget : public QWidget, public WidgetSettings, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit AttackSideWidget(QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~AttackSideWidget();
 public slots:
  void chooseRightSide(bool choose);

 private:
  Ui::AttackSideWidget* ui;
  QAction* viewAction;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_ATTACKSIDEWIDGET_H
