#ifndef PLAYPAUSEWIDGET_H
#define PLAYPAUSEWIDGET_H

#include <QWidget>
#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"

namespace Ui {
  class PlayPauseWidget;
}

class PlayPauseWidget : public QWidget,
                        public WidgetSettings,
                        public MenuBarOptions {
  Q_OBJECT

 public:
  explicit PlayPauseWidget(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
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

#endif // PLAYPAUSEWIDGET_H
