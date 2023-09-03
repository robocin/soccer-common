#include "ParametersDialogBase.h"
#include "ui_ParametersDialogBase.h"

ParametersDialogBase::ParametersDialogBase(const QString& title, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ParametersDialogBase) {
  ui->setupUi(this);
  setWindowTitle(title);
}

ParametersDialogBase::~ParametersDialogBase() {
  delete ui;
}

void ParametersDialogBase::addWidget(QWidget* widget) {
  ui->parametersLayout->addWidget(widget);
}

void ParametersDialogBase::on_buttonBox_clicked(QAbstractButton* button) {
  if (button == ui->buttonBox->button(QDialogButtonBox::Open)) {
    onOpenButtonClicked();
  } else if (button == ui->buttonBox->button(QDialogButtonBox::Save)) {
    onSaveButtonClicked();
  } else if (button == ui->buttonBox->button(QDialogButtonBox::Cancel)) {
    onCancelButtonClicked();
  } else if (button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
    onOkButtonClicked();
  } else if (button == ui->buttonBox->button(QDialogButtonBox::Apply)) {
    onApplyButtonClicked();
  }
}

void ParametersDialogBase::on_searchButtonBox_clicked(QAbstractButton* button) {
  if (button == ui->searchButtonBox->button(QDialogButtonBox::Cancel)) {
    // onCancelSearchButtonClicked();
  } else if (button == ui->searchButtonBox->button(QDialogButtonBox::Ok)) {
    // onOkSearchButtonClicked();
  }
}
