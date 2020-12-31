#include "ScoreboardWidget.h"
#include "ui_ScoreboardWidget.h"

#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ScoreboardWidget::ScoreboardWidget(
    QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(this, parent),
    MenuBarOptions(parent),
    ui(new Ui::ScoreboardWidget),
    viewAction(Factory::toggleViewAction(this)) {
  ui->setupUi(this);
  ui->labelX->setRatio(0.5);
}

ScoreboardWidget::~ScoreboardWidget() {
  delete ui;
}

void ScoreboardWidget::setFirstTeamColor(const QColor& color) {
  QPalette palette;
  palette.setColor(QPalette::Window, color);
  ui->firstTeamColor->setAutoFillBackground(true);
  ui->firstTeamColor->setPalette(palette);
}

void ScoreboardWidget::setSecondTeamColor(const QColor& color) {
  QPalette palette;
  palette.setColor(QPalette::Window, color);
  ui->secondTeamColor->setAutoFillBackground(true);
  ui->secondTeamColor->setPalette(palette);
}

void ScoreboardWidget::setScore(int first, int second) {
  ui->firstTeamScore->setText(QString::number(first));
  ui->secondTeamScore->setText(QString::number(second));
}

void ScoreboardWidget::writeLocalSettings(QSettings& settings) {
  settings.setValue("firstTeamScore", ui->firstTeamScore->text());
  settings.setValue("secondTeamScore", ui->secondTeamScore->text());

  settings.setValue("firstTeamColor",
                    ui->firstTeamColor->palette().color(QPalette::Window));
  settings.setValue("secondTeamColor",
                    ui->secondTeamColor->palette().color(QPalette::Window));

  settings.setValue("viewAction", viewAction->isChecked());
}

void ScoreboardWidget::loadLocalSettings(const QSettings& settings) {
  /* score */ {
    int first = 0;
    if (settings.contains("firstTeamScore")) {
      QString firstTeam = settings.value("firstTeamScore").value<QString>();
      first = firstTeam.toInt();
    }
    int second = 0;
    if (settings.contains("secondTeamScore")) {
      QString secondTeam = settings.value("secondTeamScore").value<QString>();
      second = secondTeam.toInt();
    }
    setScore(first, second);
  }

  if (settings.contains("firstTeamColor")) {
    QColor color = settings.value("firstTeamColor").value<QColor>();
    setFirstTeamColor(color);
  }

  if (settings.contains("secondTeamColor")) {
    QColor color = settings.value("secondTeamColor").value<QColor>();
    setSecondTeamColor(color);
  }

  if (settings.contains("viewAction")) {
    bool view = settings.value("viewAction").value<bool>();
    viewAction->setChecked(view);
  }
}

void ScoreboardWidget::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Informations"].addAction(viewAction);
}
