#ifndef SSL_UNIFICATION_PLAYPAUSECOMMUNICATIONWIDGET_H
#define SSL_UNIFICATION_PLAYPAUSECOMMUNICATIONWIDGET_H

#include <QWidget>
#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"

namespace Ui {
  class PlayPauseCommunicationWidget;
}

class PlayPauseCommunicationWidget : public QWidget, public WidgetSettings, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit PlayPauseCommunicationWidget(
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~PlayPauseCommunicationWidget();

  bool isClicked() const;

 signals:
  void onPushButtonClicked(bool checked);

 public slots:
  void click();
  void setRunning(bool runningState);

 private slots:
  void on_pushButton_clicked(bool checked);

 private:
  Ui::PlayPauseCommunicationWidget* ui;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;
};

#endif // SSL_UNIFICATION_PLAYPAUSECOMMUNICATIONWIDGET_H
