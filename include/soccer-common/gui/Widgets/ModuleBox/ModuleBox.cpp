#include "ModuleBox.h"
#include "ui_ModuleBox.h"

#include "soccer-common/gui/guiUtils/guiUtils.h"
#include "soccer-common/gui/Widgets/ParametersDialog/ParametersDialog.h"
#include "soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h"

ModuleBox::ModuleBox(const QString& name,
                     QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    QWidget(parent),
    WidgetSettings(name, parent),
    MenuBarOptions(parent),
    ui(new Ui::ModuleBox),
    viewAction(Factory::toggleViewAction(name, this)) {
  ui->setupUi(this);
  ui->moduleGroupBox->setTitle(name);

  parametersDialog = new ParametersDialog(name, this);
  parametersDialog->setWindowFlags(Qt::Window);
}

ModuleBox::~ModuleBox() {
  delete ui;
}

QString ModuleBox::currentText() const {
  return ui->comboBox->currentText();
}

ParametersDialog* ModuleBox::dialog() const {
  return parametersDialog;
}

void ModuleBox::setComboBoxEnabled(bool enabled) {
  enabled = enabled && (ui->comboBox->count() > 1);
  ui->comboBox->setEnabled(enabled);
}

void ModuleBox::setComboBoxItems(const QStringList& options) {
  ui->comboBox->clear();
  ui->comboBox->setEditable(true);
  auto font = ui->comboBox->lineEdit()->font();
  font.setBold(true);
  ui->comboBox->lineEdit()->setFont(font);
  ui->comboBox->lineEdit()->setReadOnly(true);
  ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
  ui->comboBox->insertItems(0, options);
  setComboBoxEnabled(true);
}

void ModuleBox::on_comboBox_currentTextChanged(const QString& arg1) {
  parametersDialog->setCurrentTitle(arg1);
  emit onCurrentTextChanged(arg1);
}

void ModuleBox::on_pushButton_clicked() {
  parametersDialog->show();
  emit onPushButtonClicked();
}

void ModuleBox::writeLocalSettings(QJsonObject& json) {
  json["comboBox"] = ui->comboBox->currentText();
}

void ModuleBox::loadLocalSettings(const QJsonObject& json) {
  if (json.contains("comboBox")) {
    int index = ui->comboBox->findText(json["comboBox"].toString());
    if (index >= 0) {
      ui->comboBox->setCurrentIndex(index);
    } else {
      qWarning().nospace() << json["comboBox"].toString()
                           << " not found inside "
                           << ui->moduleGroupBox->title() << ".";
    }
  }
}

void ModuleBox::writeLocalSettings(QSettings& settings) {
  settings.setValue("viewAction", viewAction->isChecked());
}

void ModuleBox::loadLocalSettings(const QSettings& settings) {
  if (settings.contains("viewAction")) {
    bool view = settings.value("viewAction").value<bool>();
    viewAction->setChecked(view);
  }
}

void ModuleBox::putWidgetActions(MainWindowMenuBar& menubar) {
  menubar["View"]["Modules"].addAction(viewAction);
}
