#ifndef SOCCER_COMMON_COLORTEAMWIDGET_H
#define SOCCER_COMMON_COLORTEAMWIDGET_H

#include <QWidget>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "soccer-common/Gui/Interfaces/Interfaces.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

namespace Ui {
  class ColorTeamWidget;
}

class ColorTeamWidget : public QWidget, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit ColorTeamWidget(QWidgetWith<MenuBarOptions> parent = nullptr);
  ~ColorTeamWidget();

 public slots:
  void setColor(const QColor& color);

 private:
  Ui::ColorTeamWidget* ui;
  QAction* viewAction;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_COLORTEAMWIDGET_H
