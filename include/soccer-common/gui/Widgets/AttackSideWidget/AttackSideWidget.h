#ifndef ATTACKSIDEWIDGET_H
#define ATTACKSIDEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

namespace Ui {
  class AttackSideWidget;
}

class AttackSideWidget : public QWidget,
                         public WidgetSettings,
                         public MenuBarOptions {
  Q_OBJECT

 public:
  explicit AttackSideWidget(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
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

#endif // TEAMSIDE_H
