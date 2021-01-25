#ifndef COLORTEAMWIDGET_H
#define COLORTEAMWIDGET_H

#include <QWidget>
#include <QtCore/QSettings>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "soccer-common/gui/Interfaces/Interfaces.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"

namespace Ui {
  class ColorTeamWidget;
}

class ColorTeamWidget : public QWidget,
                        public WidgetSettings,
                        public MenuBarOptions {
  Q_OBJECT

 public:
  explicit ColorTeamWidget(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~ColorTeamWidget();
 public slots:
  void setColor(QString color);

 private:
  Ui::ColorTeamWidget* ui;
  QAction* viewAction;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;
  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // COLORTEAMWIDGET_H
