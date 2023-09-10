#include "ParametersWindow.h"
#include "ui_ParametersWindow.h"

#include "soccer-common/Gui/Widgets/ParameterWidget/ParameterWidget.h"
#include "soccer-common/Parameters/Parameters.h"

#include <QTabWidget>

ParametersWindow::ParametersWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ParametersWindow) {
  ui->setupUi(this);
}

ParametersWindow::~ParametersWindow() {
  delete ui;
}

void ParametersWindow::build(QMap<QStringList, ParameterWidget*>& widgets,
                             const QString& name,
                             const QJsonObject& json) {
  clear();
  QStringList currentPath;
  build(widgets, currentPath, name, json);
}

void ParametersWindow::build(QMap<QStringList, ParameterWidget*>& widgets,
                             QStringList& currentPath,
                             const QString& name,
                             const QJsonObject& json) {
  ui->groupBox->setTitle(name + ":");

  QStringList keys = json.keys();
  keys.sort(Qt::CaseInsensitive);

  for (const QString& key : keys) {
    currentPath.push_back(key);

    if (key == Parameters::Detail::Tab) {
      addParametersTab(widgets, currentPath, key, json[key].toObject());
    } else if (Parameters::isParameterType(json[key].toObject())) {
      addParameterWidget(widgets, currentPath, key, json[key].toObject());
    } else {
      addParametersWindow(widgets, currentPath, key, json[key].toObject());
    }

    currentPath.pop_back();
  }
}

void ParametersWindow::clear() {
  auto layout = ui->scrollAreaLayout;

  QLayoutItem* child;
  while ((child = layout->takeAt(0)) != nullptr) {
    delete child->widget();
    delete child;
  }
}

bool ParametersWindow::showOnly(const QString& name) {
  auto layout = ui->scrollAreaLayout;
  int layoutSize = layout->count();
  bool found = false;
  for (int i = 0; i < layoutSize; ++i) {
    auto currentWidget = layout->itemAt(i)->widget();
    if (name == currentWidget->objectName()) {
      currentWidget->show();
      found = true;
    } else {
      currentWidget->hide();
    }
  }
  return found;
}

void ParametersWindow::addParameterWidget(QMap<QStringList, ParameterWidget*>& widgets,
                                          QStringList& currentPath,
                                          const QString& name,
                                          const QJsonObject& json) {
  ParameterWidget* p = new ParameterWidget(ui->scrollAreaWidgetContents);
  p->setObjectName(name);
  p->build(widgets, currentPath, name, json);
  ui->scrollAreaLayout->addWidget(p);
}

void ParametersWindow::addParametersWindow(QMap<QStringList, ParameterWidget*>& widgets,
                                           QStringList& currentPath,
                                           const QString& name,
                                           const QJsonObject& json) {
  ParametersWindow* pw = new ParametersWindow(ui->scrollAreaWidgetContents);
  pw->setObjectName(name);
  pw->build(widgets, currentPath, name, json);
  ui->scrollAreaLayout->addWidget(pw);
}

void ParametersWindow::addParametersTab(QMap<QStringList, ParameterWidget*>& widgets,
                                        QStringList& currentPath,
                                        const QString& name,
                                        const QJsonObject& json) {
  auto addSingleTab = [&](const QString& tabName, QTabWidget* tabWidget) {
    ParametersWindow* pw = new ParametersWindow(tabWidget);

    pw->setObjectName(tabName);
    pw->build(widgets, currentPath, tabName, json[tabName].toObject());
    pw->ui->groupBox->setTitle(""); // Avoid showing the name of the tab in the group box.

    tabWidget->addTab(pw, tabName);
  };

  QTabWidget* tabWidget = new QTabWidget(ui->scrollAreaWidgetContents);
  ui->scrollAreaLayout->addWidget(tabWidget);

  for (const QString& tab : json.keys()) {
    currentPath.push_back(tab);
    addSingleTab(tab, tabWidget);
    currentPath.pop_back();
  }
}