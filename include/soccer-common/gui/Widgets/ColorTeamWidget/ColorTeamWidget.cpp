#include "ColorTeamWidget.h"
#include "ui_ColorTeamWidget.h"
#include <QtCore>
#include <QtWidgets>
#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ColorTeamWidget::ColorTeamWidget(
    QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::ColorTeamWidget),
    viewAction(Factory::toggleViewActionAndConnect(this)) {
  ui->setupUi(this);
}

ColorTeamWidget::~ColorTeamWidget() {
  delete ui;
}

void ColorTeamWidget::setColor(QString color) {
  QColor cor(color);
  QGraphicsScene* scene;
  scene = new QGraphicsScene(this);
  scene->setBackgroundBrush(cor);
  ui->colorView->setScene(scene);
  ui->colorView->setBackgroundBrush(scene->backgroundBrush().color());
}

void ColorTeamWidget::writeLocalSettings(QSettings& settings) {
  settings.setValue("teamColor",
                    ui->colorView->backgroundBrush().color().name());
}

void ColorTeamWidget::loadLocalSettings(const QSettings& settings) {
  QString savedColor = settings.value("teamColor").value<QString>();
  setColor(savedColor);
}
void ColorTeamWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
