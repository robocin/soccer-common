#include "ParameterWidget.h"
#include "ui_ParameterWidget.h"

#include "soccer-common/Gui/GuiUtils/GuiUtils.h"
#include "soccer-common/Gui/Widgets/InputWidgets/InputWidgets.h"
#include "soccer-common/Gui/Widgets/ParametersWindow/ParametersWindow.h"
#include "soccer-common/Parameters/Parameters.h"

namespace InputType = Parameters::InputType;

ParameterWidget::ParameterWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget),
    inputMethod(nullptr),
    conditionalParameters(nullptr) {
  ui->setupUi(this);
  inputMethodBuildMap[InputType::Text] = std::bind(&ParameterWidget::buildTextEdit,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2);
  inputMethodBuildMap[InputType::File] = std::bind(&ParameterWidget::buildFileDialog,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2);
  inputMethodBuildMap[InputType::Directory] = std::bind(&ParameterWidget::buildDirectoryDialog,
                                                        this,
                                                        std::placeholders::_1,
                                                        std::placeholders::_2);
  inputMethodBuildMap[InputType::Slider] =
      std::bind(&ParameterWidget::buildSlider, this, std::placeholders::_1, std::placeholders::_2);
  inputMethodBuildMap[InputType::SpinBox] =
      std::bind(&ParameterWidget::buildSpinBox, this, std::placeholders::_1, std::placeholders::_2);
  inputMethodBuildMap[InputType::DoubleSpinBox] = std::bind(&ParameterWidget::buildDoubleSpinBox,
                                                            this,
                                                            std::placeholders::_1,
                                                            std::placeholders::_2);
  inputMethodBuildMap[InputType::ComboBox] = std::bind(&ParameterWidget::buildComboBox,
                                                       this,
                                                       std::placeholders::_1,
                                                       std::placeholders::_2);
  inputMethodBuildMap[InputType::CheckBox] = std::bind(&ParameterWidget::buildCheckBox,
                                                       this,
                                                       std::placeholders::_1,
                                                       std::placeholders::_2);
  inputMethodBuildMap[InputType::PushButton] = std::bind(&ParameterWidget::buildPushButton,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2);
}

ParameterWidget::~ParameterWidget() {
  delete ui;
  delete inputMethod;
}

QStringList ParameterWidget::path() const {
  return parameterPath;
}

InputWidgets::InputMethod* ParameterWidget::input() {
  return inputMethod;
}

void ParameterWidget::build(QMap<QStringList, ParameterWidget*>& widgets,
                            QStringList& currentPath,
                            const QString& name,
                            const QJsonObject& json) {
  /* inserting inside map and saving path */ {
    parameterPath = currentPath;
    widgets.insert(parameterPath, this);
  }
  QString inputType = "• " + QString(Parameters::Detail::Type) + ": " +
                      json[Parameters::Detail::Type].toString() + ";";
  QString defaultValue = json[Parameters::Detail::Value].toVariant().toString();
  if (defaultValue.isEmpty()) {
    defaultValue = Utils::quoted(defaultValue);
  }
  defaultValue = "• Default" + QString(Parameters::Detail::Value) + ": " + defaultValue + ";";
  QStringList details;
  ui->label->setTextFormat(Qt::TextFormat::MarkdownText);
  ui->label->setText(Markdown::bold(name) + ":");

  if (!json[Parameters::Detail::Description].toString().isEmpty()) {
    details += "• " + QString(Parameters::Detail::Description) + ": " +
               json[Parameters::Detail::Description].toString() + ";";
  }
  details += inputType;
  details += defaultValue;

  inputMethod = inputMethodBuildMap[json[Parameters::Detail::InputType].toString()](json, details);
  QObject::connect(inputMethod,
                   &InputWidgets::InputMethod::onValueChanged,
                   this,
                   &ParameterWidget::receiveOnValueChanged);
  QSizePolicy inputMethodSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  inputMethod->setSizePolicy(inputMethodSizePolicy);
  ui->mainWidgetLayout->addWidget(inputMethod);

  if (json.contains(Parameters::Detail::Conditional)) {
    QStringList conditionals = json[Parameters::Detail::Conditional].toObject().keys();
    conditionals.sort(Qt::CaseInsensitive);
    details += "• " + QString(Parameters::Detail::Conditional) +
               QString(conditionals.size() > 1 ? "s" : "") + ": [" + conditionals.join(", ") + "];";
    conditionalParameters = new ParametersWindow(ui->conditionalWidget);
    ui->conditionalWidgetLayout->addWidget(conditionalParameters);
    conditionalParameters->build(widgets,
                                 currentPath,
                                 Parameters::Detail::Conditional,
                                 json[Parameters::Detail::Conditional].toObject());
    showConditionalOrHide();
  } else {
    ui->conditionalWidget->hide();
  }
  ui->mainWidget->setToolTip(details.join('\n'));
}

void ParameterWidget::showConditionalOrHide() {
  if (conditionalParameters) {
    if (!conditionalParameters->showOnly(inputMethod->currentValue())) {
      ui->conditionalWidget->hide();
    } else {
      ui->conditionalWidget->show();
    }
  }
}

InputWidgets::InputMethod* ParameterWidget::buildTextEdit(const QJsonObject& json,
                                                          QStringList& details) {
  QString regex = "• " + QString(Parameters::Detail::Regex) + ": " +
                  Utils::quoted(json[Parameters::Detail::Regex].toString()) + ";";
  details += regex;
  return new InputWidgets::TextEdit(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildFileDialog(const QJsonObject& json,
                                                            QStringList& details) {

  QString filter = json[Parameters::Detail::Filter].toVariant().toString();
  if (filter.isEmpty()) {
    filter = Utils::quoted(filter);
  }
  filter = "• " + QString(Parameters::Detail::Filter) + ": " + filter + ";";
  QString defaultDirectory = json[Parameters::Detail::DefaultDirectory].toVariant().toString();
  if (defaultDirectory.isEmpty()) {
    defaultDirectory = Utils::quoted(defaultDirectory);
  }
  defaultDirectory =
      "• " + QString(Parameters::Detail::DefaultDirectory) + ": " + defaultDirectory + ";";
  details += filter;
  details += defaultDirectory;
  return new InputWidgets::FileDialog(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildDirectoryDialog(const QJsonObject& json,
                                                                 QStringList& details) {

  QString options = json[Parameters::Detail::Options].toVariant().toString();
  if (options.isEmpty()) {
    options = Utils::quoted(options);
  }
  options = "• " + QString(Parameters::Detail::Options) + ": " + options + ";";
  QString defaultDirectory = json[Parameters::Detail::DefaultDirectory].toVariant().toString();
  if (defaultDirectory.isEmpty()) {
    defaultDirectory = Utils::quoted(defaultDirectory);
  }
  defaultDirectory =
      "• " + QString(Parameters::Detail::DefaultDirectory) + ": " + defaultDirectory + ";";
  details += options;
  details += defaultDirectory;
  return new InputWidgets::DirectoryDialog(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildSlider(const QJsonObject& json,
                                                        QStringList& details) {
  QString minValue = "• " + QString(Parameters::Detail::MinValue) + ": " +
                     json[Parameters::Detail::MinValue].toVariant().toString() + ";";
  QString maxValue = "• " + QString(Parameters::Detail::MaxValue) + ": " +
                     json[Parameters::Detail::MaxValue].toVariant().toString() + ";";
  details += minValue;
  details += maxValue;
  return new InputWidgets::Slider(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildSpinBox(const QJsonObject& json,
                                                         QStringList& details) {
  QString minValue = "• " + QString(Parameters::Detail::MinValue) + ": " +
                     json[Parameters::Detail::MinValue].toVariant().toString() + ";";
  QString maxValue = "• " + QString(Parameters::Detail::MaxValue) + ": " +
                     json[Parameters::Detail::MaxValue].toVariant().toString() + ";";
  details += minValue;
  details += maxValue;
  return new InputWidgets::SpinBox(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildDoubleSpinBox(const QJsonObject& json,
                                                               QStringList& details) {
  QString minValue = "• " + QString(Parameters::Detail::MinValue) + ": " +
                     json[Parameters::Detail::MinValue].toVariant().toString() + ";";
  QString maxValue = "• " + QString(Parameters::Detail::MaxValue) + ": " +
                     json[Parameters::Detail::MaxValue].toVariant().toString() + ";";
  QString precision = "• " + QString(Parameters::Detail::Precision) + ": " +
                      json[Parameters::Detail::Precision].toVariant().toString() + " digits;";
  details += minValue;
  details += maxValue;
  details += precision;
  return new InputWidgets::DoubleSpinBox(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildComboBox(const QJsonObject& json,
                                                          QStringList& details) {
  QJsonArray itemsAsJson = json[Parameters::Detail::Options].toArray();
  QStringList itemsAsStringList;
  for (const auto& object : itemsAsJson) {
    itemsAsStringList += object.toVariant().toString();
  }
  details +=
      "• " + QString(Parameters::Detail::Options) + ": [" + itemsAsStringList.join(", ") + "];";
  return new InputWidgets::ComboBox(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildCheckBox(const QJsonObject& json, QStringList&) {
  return new InputWidgets::CheckBox(json, ui->mainWidget);
}

InputWidgets::InputMethod* ParameterWidget::buildPushButton(const QJsonObject& json,
                                                            QStringList& details) {
  details.pop_back(); // default value.
  return new InputWidgets::PushButton(json, ui->mainWidget);
}

void ParameterWidget::receiveOnValueChanged() {
  showConditionalOrHide();
}
