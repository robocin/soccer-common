#include "AttackSideWidget.h"
#include "ui_AttackSideWidget.h"

#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

AttackSideWidget::AttackSideWidget(QWidgetWith<MenuBarOptions> parent) :
    QWidget(parent),
    MenuBarOptions(parent),
    ui(new Ui::AttackSideWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

AttackSideWidget::~AttackSideWidget() {
  delete ui;
}

void AttackSideWidget::setRightSide(bool isRight) {
  if (isRight) {
    ui->side->setText("Right");
  } else {
    ui->side->setText("Left");
  }
}

void AttackSideWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Information"].addAction(viewAction);
}
