#ifndef SOCCER_COMMON_PARAMETERSDIALOGBASE_H
#define SOCCER_COMMON_PARAMETERSDIALOGBASE_H

#include <QWidget>
#include <QPushButton>
#include <QAbstractButton>

#include <QDebug>

namespace Ui {
  class ParametersDialogBase;
}

class ParametersDialogBase : public QWidget {
  Q_OBJECT

 public:
  explicit ParametersDialogBase(const QString& title, QWidget* parent = nullptr);
  ~ParametersDialogBase() override;

 protected:
  void addWidget(QWidget* widget);

  virtual void onOpenButtonClicked() = 0;
  virtual void onSaveButtonClicked() = 0;
  virtual void onCancelButtonClicked() = 0;
  virtual void onOkButtonClicked() = 0;
  virtual void onApplyButtonClicked() = 0;

 private slots:
  void on_buttonBox_clicked(QAbstractButton* button);

 private:
  Ui::ParametersDialogBase* ui;
};

#endif // SOCCER_COMMON_PARAMETERSDIALOGBASE_H
