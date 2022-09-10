#include "RefereeCommandWidget.h"
#include "ui_RefereeCommandWidget.h"

#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

RefereeCommandWidget::RefereeCommandWidget(QWidgetWith<MenuBarOptions> parent) :
    QWidget(parent),
    MenuBarOptions(parent),
    ui(new Ui::RefereeCommandWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

RefereeCommandWidget::~RefereeCommandWidget() {
  delete ui;
}

void RefereeCommandWidget::setRefereeCommand(const QString& command) {
  ui->command->setText(command);
}

void RefereeCommandWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Information"].addAction(viewAction);
}
