#ifndef SOCCER_COMMON_PLAYPAUSEWIDGET_H
#define SOCCER_COMMON_PLAYPAUSEWIDGET_H

#include <QWidget>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class PlayPauseWidget;
}

class PlayPauseWidget : public QWidget, public WidgetSettings, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit PlayPauseWidget(QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~PlayPauseWidget();

  bool isClicked() const;

 signals:
  void onPushButtonClicked(bool checked);

 public slots:
  void click();
  void setRunning(bool runningState);

 private slots:
  void on_pushButton_clicked(bool checked);

 private:
  Ui::PlayPauseWidget* ui;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SOCCER_COMMON_PLAYPAUSEWIDGET_H
