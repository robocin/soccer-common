#ifndef SSL_UNIFICATION_PARAMETERSDIALOG_H
#define SSL_UNIFICATION_PARAMETERSDIALOG_H

#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/GuiFactory/GuiFactory.h"
#include "soccer-common/Gui/Interfaces/Interfaces.h"
#include "soccer-common/Gui/AbstractWidgets/AbstractWidgets.h"
#include "soccer-common/Parameters/Parameters.h"

class ParameterWidget;
class ParametersWindow;

class ParametersDialog : public SearchableParametersDialogBase, public WidgetSettings {
  Q_OBJECT

  QString m_title;
  QMap<QString, Parameters::JsonHandler> m_jsons;
  ParametersWindow* m_parametersWindow;
  QMap<QStringList, ParameterWidget*> m_widgets;

 public:
  explicit ParametersDialog(const QString& title,
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
  Parameters::UpdateRequests getUpdates(bool overwriteBackup, bool allValues = false) const;

  void openCurrentFromJsonHandler(const Parameters::JsonHandler& json);
  void updateCurrentAndEmit(bool allValues = false);

  void onOpenButtonClicked() override;
  void onSaveButtonClicked() override;

  void closeEvent(QCloseEvent*) override;
  void onCancelButtonClicked() override;

  void onApplyButtonClicked() override;
  void onOkButtonClicked() override;

  void onOkSearchButtonClicked() override;
  void onCancelSearchButtonClicked() override;

  void writeLocalSettings(QSettings& settings) override;
  void loadLocalSettings(const QSettings& settings) override;

  void writeLocalSettings(QJsonObject& json) override;
  void loadLocalSettings(const QJsonObject& json) override;
};

#endif // SSL_UNIFICATION_PARAMETERSDIALOG_H
