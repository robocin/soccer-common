#include "InputWidgets.h"

#include "soccer-common/Parameters/Parameters.h"

using namespace Parameters;

InputWidgets::InputMethod::InputMethod(QWidget* parent) : QWidget(parent) {
  setLayout(&inputMethodLayout);
  inputMethodLayout.setSpacing(5);
  inputMethodLayout.setContentsMargins(0, 0, 0, 0);
}

InputWidgets::InputMethod::~InputMethod() {
}

void InputWidgets::InputMethod::reciveOnValueChanged() {
  emit onValueChanged();
}

InputWidgets::TextEdit::TextEdit(const QJsonObject& json, QWidget* parent) :
    InputMethod(parent) {
  QObject::connect(&textEdit,
                   &QTextEdit::textChanged,
                   this,
                   &InputWidgets::TextEdit::reciveOnValueChanged);
  inputMethodLayout.addWidget(&textEdit);
  regex.setPattern(json[Detail::Regex].toVariant().toString());
  QString value = json[Detail::Value].toVariant().toString();
  Q_ASSERT(regex.match(value).hasMatch());
  textEdit.setText(value);
  textEdit.setAlignment(Qt::AlignCenter);
  backup = textEdit.toPlainText();
}

void InputWidgets::TextEdit::set(const QString& value) {
  if (regex.match(value).hasMatch()) {
    textEdit.setText(value);
    textEdit.setAlignment(Qt::AlignCenter);
  }
}

QString InputWidgets::TextEdit::backupValue() const {
  return backup;
}

QString InputWidgets::TextEdit::currentValue() const {
  return textEdit.toPlainText();
}

void InputWidgets::TextEdit::storeCurrent() {
  QString value = textEdit.toPlainText();
  if (regex.match(value).hasMatch()) {
    backup = textEdit.toPlainText();
  } else {
    qWarning() << "the current value" << value
               << "doesn't match, loading backup" << backup << "instead.";
    loadBackup();
  }
}

void InputWidgets::TextEdit::loadBackup() {
  textEdit.setText(backup);
  textEdit.setAlignment(Qt::AlignCenter);
}

InputWidgets::Slider::Slider(const QJsonObject& json, QWidget* parent) :
    InputMethod(parent) {
  slider.slider.setOrientation(Qt::Horizontal);
  slider.label.setAlignment(Qt::AlignCenter);
  QObject::connect(&slider.slider,
                   &QSlider::valueChanged,
                   this,
                   &InputWidgets::Slider::reciveOnValueChanged);
  QObject::connect(&slider.slider,
                   &QSlider::valueChanged,
                   &slider.label,
                   [&](int value) {
                     slider.label.setText(QString::number(value));
                   });
  inputMethodLayout.addWidget(&slider.slider);
  inputMethodLayout.addWidget(&slider.label);
  int minValue = json[Detail::MinValue].toInt();
  int maxValue = json[Detail::MaxValue].toInt();
  int value = json[Detail::Value].toInt();
  slider.slider.setRange(minValue, maxValue);
  slider.slider.setValue(value);
  backup = QString::number(slider.slider.value());
}

void InputWidgets::Slider::set(const QString& value) {
  slider.slider.setValue(value.toInt());
}

QString InputWidgets::Slider::backupValue() const {
  return backup;
}

QString InputWidgets::Slider::currentValue() const {
  return QString::number(slider.slider.value());
}

void InputWidgets::Slider::storeCurrent() {
  backup = QString::number(slider.slider.value());
}

void InputWidgets::Slider::loadBackup() {
  slider.slider.setValue(backup.toInt());
}

InputWidgets::SpinBox::SpinBox(const QJsonObject& json, QWidget* parent) :
    InputMethod(parent) {
  QObject::connect(&spinBox,
                   qOverload<int>(&QSpinBox::valueChanged),
                   this,
                   &InputWidgets::SpinBox::reciveOnValueChanged);
  inputMethodLayout.addWidget(&spinBox);
  int minValue = json[Detail::MinValue].toInt();
  int maxValue = json[Detail::MaxValue].toInt();
  int value = json[Detail::Value].toInt();
  spinBox.setRange(minValue, maxValue);
  spinBox.setValue(value);
  backup = spinBox.text();
}

void InputWidgets::SpinBox::set(const QString& value) {
  spinBox.setValue(value.toInt());
}

QString InputWidgets::SpinBox::backupValue() const {
  return backup;
}

QString InputWidgets::SpinBox::currentValue() const {
  return QString::number(spinBox.value());
}

void InputWidgets::SpinBox::storeCurrent() {
  backup = spinBox.text();
}

void InputWidgets::SpinBox::loadBackup() {
  spinBox.setValue(backup.toInt());
}

InputWidgets::DoubleSpinBox::DoubleSpinBox(const QJsonObject& json,
                                           QWidget* parent) :
    InputMethod(parent) {
  QObject::connect(&doubleSpinBox,
                   qOverload<double>(&QDoubleSpinBox::valueChanged),
                   this,
                   &InputWidgets::DoubleSpinBox::reciveOnValueChanged);
  inputMethodLayout.addWidget(&doubleSpinBox);

  int precision = json[Detail::Precision].toVariant().toInt();
  doubleSpinBox.setDecimals(precision);

  double minValue = json[Detail::MinValue].toDouble();
  double maxValue = json[Detail::MaxValue].toDouble();
  doubleSpinBox.setRange(minValue, maxValue);

  double value = json[Detail::Value].toDouble();
  doubleSpinBox.setValue(value);

  backup = doubleSpinBox.text();
}

void InputWidgets::DoubleSpinBox::set(const QString& value) {
  doubleSpinBox.setValue(value.toDouble());
}

QString InputWidgets::DoubleSpinBox::backupValue() const {
  return backup;
}

QString InputWidgets::DoubleSpinBox::currentValue() const {
  return doubleSpinBox.text();
}

void InputWidgets::DoubleSpinBox::storeCurrent() {
  backup = doubleSpinBox.text();
}

void InputWidgets::DoubleSpinBox::loadBackup() {
  doubleSpinBox.setValue(backup.toDouble());
}

Qt::CheckState InputWidgets::CheckBox::checkStateFromBoolean(bool value) const {
  return value ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
}

bool InputWidgets::CheckBox::booleanFromCheckState(
    Qt::CheckState checkState) const {
  return checkState == Qt::CheckState::Checked;
}

InputWidgets::CheckBox::CheckBox(const QJsonObject& json, QWidget* parent) :
    InputMethod(parent) {
  QObject::connect(&checkBox,
                   &QCheckBox::stateChanged,
                   this,
                   &InputWidgets::CheckBox::reciveOnValueChanged);
  checkBox.setLayoutDirection(Qt::RightToLeft);
  inputMethodLayout.addWidget(&checkBox);
  checkBox.setCheckState(
      checkStateFromBoolean(json[Detail::Value].toVariant().toBool()));
  backup = booleanFromCheckState(checkBox.checkState());
}

void InputWidgets::CheckBox::set(const QString& value) {
  checkBox.setCheckState(checkStateFromBoolean(QVariant(value).toBool()));
}

QString InputWidgets::CheckBox::backupValue() const {
  return backup ? "true" : "false";
}

QString InputWidgets::CheckBox::currentValue() const {
  return booleanFromCheckState(checkBox.checkState()) ? "true" : "false";
}

void InputWidgets::CheckBox::storeCurrent() {
  backup = booleanFromCheckState(checkBox.checkState());
}

void InputWidgets::CheckBox::loadBackup() {
  checkBox.setCheckState(checkStateFromBoolean(backup));
}

InputWidgets::ComboBox::ComboBox(const QJsonObject& json, QWidget* parent) :
    InputMethod(parent) {
  QObject::connect(&comboBox,
                   &QComboBox::currentTextChanged,
                   this,
                   &InputWidgets::ComboBox::reciveOnValueChanged);
  inputMethodLayout.addWidget(&comboBox);
  QString value = json[Detail::Value].toVariant().toString();
  QJsonArray itemsAsJson = json[Detail::Options].toArray();
  QStringList itemsAsStringList;

  for (const QJsonValue& object : itemsAsJson) {
    itemsAsStringList += object.toVariant().toString();
  }

  comboBox.addItems(itemsAsStringList);
  comboBox.setCurrentText(value);
  backup = comboBox.currentText();
}

void InputWidgets::ComboBox::set(const QString& value) {
  if (comboBox.findText(value) >= 0) {
    comboBox.setCurrentText(value);
  }
}

QString InputWidgets::ComboBox::backupValue() const {
  return backup;
}

QString InputWidgets::ComboBox::currentValue() const {
  return comboBox.currentText();
}

void InputWidgets::ComboBox::storeCurrent() {
  backup = comboBox.currentText();
}

void InputWidgets::ComboBox::loadBackup() {
  comboBox.setCurrentText(backup);
}
