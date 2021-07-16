#include "ScoreboardWidget.h"
#include "ui_ScoreboardWidget.h"

#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ScoreboardWidget::ScoreboardWidget(QWidgetWith<MenuBarOptions> parent) :
    QWidget(parent),
    MenuBarOptions(parent),
    ui(new Ui::ScoreboardWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
  ui->labelX->setRatio(0.5);
}

ScoreboardWidget::~ScoreboardWidget() {
  delete ui;
}

void ScoreboardWidget::setColor(const QColor& firstColor, const QColor& secondColor) {
  {
    QPalette palette;
    palette.setColor(QPalette::Window, firstColor);
    ui->firstTeamColor->setAutoFillBackground(true);
    ui->firstTeamColor->setPalette(palette);
  }
  {
    QPalette palette;
    palette.setColor(QPalette::Window, secondColor);
    ui->secondTeamColor->setAutoFillBackground(true);
    ui->secondTeamColor->setPalette(palette);
  }
}

void ScoreboardWidget::setScore(int first, int second) {
  ui->firstTeamScore->setText(QString::number(first));
  ui->secondTeamScore->setText(QString::number(second));
}

void ScoreboardWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Information"].addAction(viewAction);
}
