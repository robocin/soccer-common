#ifndef SSL_UNIFICATION_SEARCHABLEPARAMETERSDIALOGBASE_H
#define SSL_UNIFICATION_SEARCHABLEPARAMETERSDIALOGBASE_H

#include <QWidget>
#include <QPushButton>
#include <QAbstractButton>

#include <QDebug>

namespace Ui {
  class SearchableParametersDialogBase;
}

class SearchableParametersDialogBase : public QWidget {
  Q_OBJECT

 public:
  explicit SearchableParametersDialogBase(const QString& title, QWidget* parent = nullptr);
  ~SearchableParametersDialogBase() override;

  QString searchText();
  void resetSearchText();

 protected:
  void addWidget(QWidget* widget);

  virtual void onOpenButtonClicked() = 0;
  virtual void onSaveButtonClicked() = 0;
  virtual void onCancelButtonClicked() = 0;
  virtual void onOkButtonClicked() = 0;
  virtual void onApplyButtonClicked() = 0;

  virtual void onCancelSearchButtonClicked() = 0;
  virtual void onOkSearchButtonClicked() = 0;

 private slots:
  void on_buttonBox_clicked(QAbstractButton* button);
  void on_searchButtonBox_clicked(QAbstractButton* button);

 private:
  Ui::SearchableParametersDialogBase* ui;
};

#endif // SSL_UNIFICATION_SEARCHABLEPARAMETERSDIALOGBASE_H
