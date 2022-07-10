#ifndef SOCCER_COMMON_REFEREECOMMANDWIDGET_H
#define SOCCER_COMMON_REFEREECOMMANDWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class RefereeCommandWidget;
}

class RefereeCommandWidget : public QWidget, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit RefereeCommandWidget(QWidgetWith<MenuBarOptions> parent = nullptr);
  ~RefereeCommandWidget();

 public slots:
  void setRefereeCommand(const QString& command);

 private:
  Ui::RefereeCommandWidget* ui;
  QAction* viewAction;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_REFEREECOMMANDWIDGET_H
