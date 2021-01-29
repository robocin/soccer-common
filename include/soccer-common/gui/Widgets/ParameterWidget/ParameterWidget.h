#ifndef SOCCER_COMMON_PARAMETERWIDGET_H
#define SOCCER_COMMON_PARAMETERWIDGET_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
  class ParameterWidget;
}

namespace InputWidgets {
  class InputMethod;
}

class ParametersWindow;

class ParameterWidget : public QWidget {
  Q_OBJECT

  friend ParametersWindow;

 public:
  explicit ParameterWidget(QWidget* parent = nullptr);
  ~ParameterWidget();

  QStringList path() const;
  InputWidgets::InputMethod* input();

 private:
  Ui::ParameterWidget* ui;
  InputWidgets::InputMethod* inputMethod;
  ParametersWindow* conditionalParameters;
  QMap<QString,
       std::function<InputWidgets::InputMethod*(const QJsonObject&,
                                                QStringList&)>>
      inputMethodBuildMap;
  QStringList parameterPath;

  void build(QMap<QStringList, ParameterWidget*>& widgets,
             QStringList& currentPath,
             const QString& name,
             const QJsonObject& json);

  void showConditionalOrHide();

  InputWidgets::InputMethod* buildTextEdit(const QJsonObject& json,
                                           QStringList& details);
  InputWidgets::InputMethod* buildSlider(const QJsonObject& json,
                                         QStringList& details);
  InputWidgets::InputMethod* buildSpinBox(const QJsonObject& json,
                                          QStringList& details);
  InputWidgets::InputMethod* buildDoubleSpinBox(const QJsonObject& json,
                                                QStringList& details);
  InputWidgets::InputMethod* buildComboBox(const QJsonObject& json,
                                           QStringList& details);
  InputWidgets::InputMethod* buildCheckBox(const QJsonObject& json,
                                           QStringList& details);

 private slots:
  void reciveOnValueChanged();
};

#endif // SOCCER_COMMON_PARAMETERWIDGET_H
