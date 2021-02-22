#include "ColorTeamWidget.h"
#include "ui_ColorTeamWidget.h"
#include <QtCore>
#include <QtWidgets>
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ColorTeamWidget::ColorTeamWidget(QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::ColorTeamWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

ColorTeamWidget::~ColorTeamWidget() {
  delete ui;
}

void ColorTeamWidget::setColor(QColor color) {
  int r, g, b;
  color.getRgb(&r, &g, &b);
  ui->Color->setText(QString::number(r) + " " + QString::number(g) + " " + QString::number(b));
}

void ColorTeamWidget::writeLocalSettings(QSettings& settings) {
  settings.setValue("teamColor", ui->Color->text());
}

void ColorTeamWidget::loadLocalSettings(const QSettings& settings) {
  QString savedColor = settings.value("teamColor").value<QString>();
  setColor(savedColor);
}
void ColorTeamWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
