#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/guiFactory/guiFactory.h"
#include "soccer-common/gui/Interfaces/Interfaces.h"
#include "soccer-common/gui/AbstractWidgets/AbstractWidgets.h"
#include "soccer-common/Parameters/Parameters.h"

class ParameterWidget;
class ParametersWindow;

class ParametersDialog : public ParametersDialogBase, public WidgetSettings {
  Q_OBJECT

  QString m_title;
  QMap<QString, Parameters::JsonHandler> m_jsons;
  ParametersWindow* m_parametersWindow;
  QMap<QStringList, ParameterWidget*> m_widgets;

 public:
  ParametersDialog(
      const QString& title,
      QWidgetWith<WidgetSettings, MenuBarOptions> parent = nullptr);
  ~ParametersDialog() override;

 signals:
  void onChangingParameters(const Parameters::UpdateRequests& update);

 public slots:
  void build(const QJsonObject& json);
  void setCurrentTitle(const QString& name);

 private:
  enum class FileNameType { Open, Save };

  QString getFileName(FileNameType type);
  Parameters::UpdateRequests getUpdates(bool overwriteBackup,
                                        bool allValues = false) const;

  void openCurrentFromJsonHandler(const Parameters::JsonHandler& json);
  void updateCurrentAndEmit(bool allValues = false);

  void onOpenButtonClicked() override;
  void onSaveButtonClicked() override;

  void closeEvent(QCloseEvent*) override;
  void onCancelButtonClicked() override;

  void onOkButtonClicked() override;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void writeLocalSettings(QJsonObject& json) override;
  void loadLocalSettings(const QJsonObject& json) override;
};

#endif // PARAMETERSDIALOG_H
