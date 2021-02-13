#include "ParametersDialog.h"
#include "soccer-common/Gui/Widgets/Widgets.h"

ParametersDialog::ParametersDialog(
    const QString& title,
    QWidgetWith<WidgetSettings, MenuBarOptions> parent) :
    ParametersDialogBase(title, parent),
    WidgetSettings(this, parent) {
  m_parametersWindow = new ParametersWindow(parent);
  m_parametersWindow->build(m_widgets, windowTitle(), QJsonObject());
  addWidget(m_parametersWindow);
}

ParametersDialog::~ParametersDialog() {
}

void ParametersDialog::build(const QJsonObject& json) {
  using namespace Parameters;
  // if the value already exists, do not insert, keeping the last modification.
  m_jsons[m_title].insert(JsonHandler::fromJsonObject(json).updates());
  m_parametersWindow->build((m_widgets.clear(), m_widgets), m_title, json);
  openCurrentFromJsonHandler(m_jsons[m_title]);
  updateCurrentAndEmit(true);
}

void ParametersDialog::setCurrentTitle(const QString& title) {
  m_title = title;
}

QString ParametersDialog::getFileName(FileNameType type) {
  QString folder =
      localConfigPath() + "modules/" + windowTitle() + "/" + m_title + "/";
  QDir().mkpath(folder);

  switch (type) {
    case FileNameType::Open: {
      return QFileDialog::getOpenFileName(this,
                                          "Open " + m_title + ":",
                                          folder,
                                          "Json (*.json)");
    }
    case FileNameType::Save: {
      return QFileDialog::getSaveFileName(this,
                                          "Save " + m_title + ":",
                                          folder,
                                          "Json (*.json)");
    }
    default: {
      throw std::runtime_error("unknown filename type.");
    }
  }
}

Parameters::UpdateRequests ParametersDialog::getUpdates(bool overwriteBackup,
                                                        bool allValues) const {
  using namespace Parameters;

  UpdateRequests updates;
  for (auto up : m_widgets) {
    auto input = up->input();
    if (allValues || (input->backupValue() != input->currentValue())) {
      updates += UpdateRequest(up->path(), input->currentValue());
      if (overwriteBackup) {
        input->storeCurrent();
      }
    }
  }
  return updates;
}

void ParametersDialog::openCurrentFromJsonHandler(
    const Parameters::JsonHandler& json) {
  auto updates = json.updates();
  for (const auto& up : updates) {
    auto it = m_widgets.find(up.path());
    if (it != m_widgets.end()) {
      if (up.value() != it.value()->input()->currentValue()) {
        it.value()->input()->set(up.value());
        qWarning().nospace() << "trying to load " << up.path()
                             << " with value: " << up.value() << ".";
      }
    }
  }
}

void ParametersDialog::updateCurrentAndEmit(bool allValues) {
  using namespace Parameters;
  UpdateRequests updates = getUpdates(true, allValues);
  if (!updates.empty()) {
    m_jsons[m_title].insert_or_assign(updates);
    qWarning() << "emitting on changing parameters:";
    for (const auto& up : updates) {
      qWarning().nospace() << up.path() << " with value: " << up.value() << ".";
    }
    emit onChangingParameters(updates);
    qWarning() << "all changed parameters were emitted.";
  }
}

void ParametersDialog::onOpenButtonClicked() {
  using namespace Parameters;

  QString jsonFile = getFileName(FileNameType::Open);
  if (!jsonFile.isEmpty()) {
    if (QFile file(jsonFile); file.open(QIODevice::ReadOnly)) {
      auto jsonHandler = JsonHandler::fromJsonObject(
          QJsonDocument::fromJson(file.readAll()).object());
      openCurrentFromJsonHandler(jsonHandler);
      qWarning() << "a configuration of" << m_title << "was loaded.";
      file.close();
    } else {
      qWarning() << "the file" << jsonFile
                 << "has not been opened for reading.";
    }
  } else {
    qWarning() << "path is empty.";
  }
}

void ParametersDialog::onSaveButtonClicked() {
  using Parameters::JsonHandler;

  QString jsonFile = getFileName(FileNameType::Save);
  if (!jsonFile.isEmpty() || jsonFile == ".json") {
    if (!jsonFile.endsWith(".json")) {
      jsonFile += ".json";
    }
    if (QFile file(jsonFile); file.open(
            QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
      JsonHandler json = m_jsons[m_title];
      json.insert_or_assign(getUpdates(false));
      file.write(json.toJson());
      qWarning() << "a configuration of" << m_title << "has been saved.";
      file.close();
    } else {
      qWarning() << "the file" << jsonFile
                 << "has not been opened for writing.";
    }
  } else {
    qWarning() << "path is empty.";
    qWarning() << "the operation was not completed and no file was created.";
  }
}

void ParametersDialog::closeEvent(QCloseEvent*) {
  onCancelButtonClicked();
}

void ParametersDialog::onCancelButtonClicked() {
  qWarning().nospace() << "discarding changes from " << m_title << ".";
  for (auto up : m_widgets) {
    auto input = up->input();
    if (input->backupValue() != input->currentValue()) {
      qWarning().nospace() << "discarding " << up->path() << ".";
      up->input()->loadBackup();
    }
  }
  hide();
}

void ParametersDialog::onApplyButtonClicked() {
  qWarning().nospace() << "saving changes from " << m_title << ".";
  updateCurrentAndEmit();
}

void ParametersDialog::onOkButtonClicked() {
  onApplyButtonClicked();
  hide();
}

void ParametersDialog::writeLocalSettings(QSettings& settings) {
  settings.setValue("geometry", geometry());
}

void ParametersDialog::loadLocalSettings(const QSettings& settings) {
  if (settings.contains("geometry")) {
    setGeometry(settings.value("geometry").value<QRect>());
  }
}

void ParametersDialog::writeLocalSettings(QJsonObject& json) {
  QStringList keys = m_jsons.keys();
  for (const QString& key : keys) {
    json[key] = QJsonDocument::fromJson(m_jsons[key].toJson()).object();
  }
}

void ParametersDialog::loadLocalSettings(const QJsonObject& json) {
  using namespace Parameters;
  QStringList keys = json.keys();
  for (const QString& key : keys) {
    auto updates = JsonHandler::fromJsonObject(json[key].toObject()).updates();
    m_jsons[key].insert_or_assign(updates);
  }
  openCurrentFromJsonHandler(m_jsons[m_title]);
  updateCurrentAndEmit();
}
