#include "ColorTeamWidget.h"
#include "ui_ColorTeamWidget.h"
#include "soccer-common/Gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ColorTeamWidget::ColorTeamWidget(QWidgetWith<MenuBarOptions> parent) :
    QWidget(parent),
    MenuBarOptions(parent),
    ui(new Ui::ColorTeamWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
}

ColorTeamWidget::~ColorTeamWidget() {
  delete ui;
}

void ColorTeamWidget::setColor(const QColor& color) {
  QGraphicsScene* scene;
  scene = new QGraphicsScene(this);
  scene->setBackgroundBrush(color);
  ui->colorView->setScene(scene);
  ui->colorView->setBackgroundBrush(scene->backgroundBrush().color());
}

void ColorTeamWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Information"].addAction(viewAction);
}
