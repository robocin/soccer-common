#include "SearchableParametersDialogBase.h"
#include "ui_SearchableParametersDialogBase.h"

SearchableParametersDialogBase::SearchableParametersDialogBase(const QString& title,
                                                               QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SearchableParametersDialogBase) {
  ui->setupUi(this);
  setWindowTitle(title);
}

QString SearchableParametersDialogBase::searchText() {
  return ui->searchTextBar->text();
}

void SearchableParametersDialogBase::resetSearchText() {
  ui->searchTextBar->clear();
}

SearchableParametersDialogBase::~SearchableParametersDialogBase() {
  delete ui;
}

void SearchableParametersDialogBase::addWidget(QWidget* widget) {
  ui->parametersLayout->addWidget(widget);
}

void SearchableParametersDialogBase::on_buttonBox_clicked(QAbstractButton* button) {
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

void SearchableParametersDialogBase::on_searchButtonBox_clicked(QAbstractButton* button) {
  if (button == ui->searchButtonBox->button(QDialogButtonBox::Cancel)) {
    onCancelSearchButtonClicked();
  } else if (button == ui->searchButtonBox->button(QDialogButtonBox::Ok)) {
    onOkSearchButtonClicked();
  }
}
