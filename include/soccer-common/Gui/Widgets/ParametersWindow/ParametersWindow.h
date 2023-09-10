#ifndef SOCCER_COMMON_PARAMETERSWINDOW_H
#define SOCCER_COMMON_PARAMETERSWINDOW_H

#include <QWidget>
#include <QJsonObject>

class QTabWidget;
class ParameterWidget;

namespace Ui {
  class ParametersWindow;
} // namespace Ui

class ParametersWindow : public QWidget {
  Q_OBJECT

  friend class ParameterWidget;

 public:
  explicit ParametersWindow(QWidget* parent = nullptr);
  ~ParametersWindow();

  void
  build(QMap<QStringList, ParameterWidget*>& widgets, const QString& name, const QJsonObject& json);
  void store();
  void load();

 private:
  Ui::ParametersWindow* ui;

  void clear();

  void build(QMap<QStringList, ParameterWidget*>& widgets,
             QStringList& currentPath,
             const QString& name,
             const QJsonObject& json);

  bool showOnly(const QString& name);

  void addParameterWidget(QMap<QStringList, ParameterWidget*>& widgets,
                          QStringList& currentPath,
                          const QString& name,
                          const QJsonObject& json);
  void addParametersWindow(QMap<QStringList, ParameterWidget*>& widgets,
                           QStringList& currentPath,
                           const QString& name,
                           const QJsonObject& json);
  void addParametersTab(QMap<QStringList, ParameterWidget*>& widgets,
                        QStringList& currentPath,
                        const QString& name,
                        const QJsonObject& json);
};

#endif // SOCCER_COMMON_PARAMETERSWINDOW_H
