#ifndef PARAMETERSDIALOGBASE_H
#define PARAMETERSDIALOGBASE_H

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
  explicit ParametersDialogBase(const QString& title,
                                QWidget* parent = nullptr);
  virtual ~ParametersDialogBase();

 protected:
  void addWidget(QWidget* widget);

  virtual void onOpenButtonClicked() = 0;
  virtual void onSaveButtonClicked() = 0;
  virtual void onCancelButtonClicked() = 0;
  virtual void onOkButtonClicked() = 0;

 private slots:
  void on_buttonBox_clicked(QAbstractButton* button);

 private:
  Ui::ParametersDialogBase* ui;
};

#endif // PARAMETERSDIALOGBASE_H