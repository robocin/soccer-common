#include "AttackSideWidget.h"
#include "ui_AttackSideWidget.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

AttackSideWidget::AttackSideWidget(
    QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::AttackSideWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

AttackSideWidget::~AttackSideWidget() {
  delete ui;
}
void AttackSideWidget::chooseRightSide(bool isRight) {
  if (isRight) {
    ui->side->setText("Right");
  } else {
    ui->side->setText("Left");
  }
}

void AttackSideWidget::writeLocalSettings(QSettings& settings) {
  settings.setValue("AttackSideWidget", ui->side->text());
}

void AttackSideWidget::loadLocalSettings(const QSettings& settings) {
  QString savedSide = settings.value("AttackSideWidget").value<QString>();
  if (savedSide == "Left") {
    chooseRightSide(false);
  } else {
    chooseRightSide(true);
  }
}
void AttackSideWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
