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

class AttackSideWidget : public QWidget, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit AttackSideWidget(QWidgetWith<MenuBarOptions> parent = nullptr);
  ~AttackSideWidget();

 public slots:
  void setRightSide(bool isRight);

 private:
  Ui::AttackSideWidget* ui;
  QAction* viewAction;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_ATTACKSIDEWIDGET_H
