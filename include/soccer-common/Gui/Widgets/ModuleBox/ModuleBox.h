#ifndef SOCCER_COMMON_MODULEBOX_H
#define SOCCER_COMMON_MODULEBOX_H

#include <QWidget>
#include "soccer-common/Gui/Interfaces/Interfaces.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"

namespace Ui {
  class ModuleBox;
}

class ParametersDialog;

class ModuleBox : public QWidget, public WidgetSettings, public MenuBarOptions {
  Q_OBJECT

 public:
  explicit ModuleBox(
      const QString& name,
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~ModuleBox();

  QString currentText() const;
  ParametersDialog* dialog() const;

 signals:
  void onCurrentTextChanged(const QString& text);
  void onPushButtonClicked();

 public slots:
  void setComboBoxEnabled(bool enabled);
  void setComboBoxItems(const QStringList& options);

 private slots:
  void on_comboBox_currentTextChanged(const QString& arg1);
  void on_pushButton_clicked();

 protected:
  void writeLocalSettings(QJsonObject& json) override;
  void loadLocalSettings(const QJsonObject& json) override;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void putWidgetActions(MainWindowMenuBar& menubar) override;

 private:
  Ui::ModuleBox* ui;
  QAction* viewAction;
  ParametersDialog* parametersDialog;
};

#endif // SOCCER_COMMON_MODULEBOX_H
