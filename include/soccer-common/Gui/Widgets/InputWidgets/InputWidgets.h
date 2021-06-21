#ifndef SOCCER_COMMON_INPUTWIDGETS_H
#define SOCCER_COMMON_INPUTWIDGETS_H

#include <QtWidgets>

namespace InputWidgets {
  class InputMethod : public QWidget {
    Q_OBJECT
   protected:
    QVBoxLayout inputMethodLayout;

   public:
    explicit InputMethod(QWidget* parent);
    virtual ~InputMethod();

    virtual bool isPushButton();

    virtual void set(const QString& value) = 0;
    virtual QString backupValue() const = 0;
    virtual QString currentValue() const = 0;
    virtual void storeCurrent() = 0;
    virtual void loadBackup() = 0;

   protected slots:
    void receiveOnValueChanged();

   signals:
    void onValueChanged();
  };

  class TextEdit : public InputMethod {
    QRegularExpression regex;
    QTextEdit textEdit;
    QString backup;

   public:
    explicit TextEdit(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class Slider : public InputMethod {
    struct SliderPrivate {
      QSlider slider;
      QLabel label;
    } slider;
    QString backup;

   public:
    explicit Slider(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class SpinBox : public InputMethod {
    QSpinBox spinBox;
    QString backup;

   public:
    explicit SpinBox(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class DoubleSpinBox : public InputMethod {
    QDoubleSpinBox doubleSpinBox;
    QString backup;

   public:
    explicit DoubleSpinBox(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class CheckBox : public InputMethod {
    QCheckBox checkBox;
    bool backup;

    Qt::CheckState checkStateFromBoolean(bool value) const;
    bool booleanFromCheckState(Qt::CheckState checkState) const;

   public:
    explicit CheckBox(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class ComboBox : public InputMethod {
    QComboBox comboBox;
    QString backup;

   public:
    explicit ComboBox(const QJsonObject& json, QWidget* parent);

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };

  class PushButton : public InputMethod {
    QPushButton pushButton;

   public:
    explicit PushButton(const QJsonObject& json, QWidget* parent);

    bool isPushButton() override;

    void set(const QString& value) override;
    QString backupValue() const override;
    QString currentValue() const override;
    void storeCurrent() override;
    void loadBackup() override;
  };
} // namespace InputWidgets

#endif // SOCCER_COMMON_INPUTWIDGETS_H
