#include "WidgetSettings.h"

void WidgetSettings::writeLocalSettings(QJsonObject&) {
}

void WidgetSettings::loadLocalSettings(const QJsonObject&) {
}

void WidgetSettings::writeSettings(QSettings& settings, QJsonObject& json) {
  // when .toObject() is called, the json object creates a copy. It means that
  // we need to pass copies and after this do assignments to use in a recursive
  // way. To avoid insert empty groups, we only assing if exists some data.
  QJsonObject currentJson(json.contains(m_groupName) ? json[m_groupName].toObject() :
                                                       QJsonObject());

  settings.beginGroup(m_groupName);
  writeLocalSettings(settings);
  writeLocalSettings(currentJson);
  for (auto widget : m_widgets) {
    widget->writeSettings(settings, currentJson);
  }
  settings.endGroup();
  if (!currentJson.isEmpty()) {
    json[m_groupName] = currentJson;
  }
}

void WidgetSettings::loadSettings(QSettings& settings, QJsonObject& json) {
  bool containsQSettings = settings.childGroups().contains(m_groupName);
  bool containsQJson = json.contains(m_groupName);
  if (!containsQSettings && !containsQJson) {
    // nothing to do.
    return;
  }

  QJsonObject currentJson(containsQJson ? json[m_groupName].toObject() : QJsonObject());

  settings.beginGroup(m_groupName);
  if (containsQSettings) {
    loadLocalSettings(settings);
  }
  if (containsQJson) {
    loadLocalSettings(currentJson);
  }
  for (auto widget : m_widgets) {
    widget->loadSettings(settings, currentJson);
  }
  settings.endGroup();
}

void WidgetSettings::setupWidgetSettings(const QString& projectName,
                                         const QString& projectVersion,
                                         const QString& projectPath,
                                         const QString& localConfigPath,
                                         const QString& executionDateTime,
                                         const QString& executionTime) {
  m_projectName = projectName;
  m_projectVersion = projectVersion;
  m_projectPath = projectPath;
  m_localConfigPath = localConfigPath;
  m_executionDateTime = executionDateTime;
  m_executionTime = executionTime;

  for (auto widget : m_widgets) {
    widget->setupWidgetSettings(projectName,
                                projectVersion,
                                projectPath,
                                localConfigPath,
                                executionDateTime,
                                executionTime);
  }
}

QString WidgetSettings::projectName() const {
  return m_projectName;
}

QString WidgetSettings::projectVersion() const {
  return m_projectVersion;
}

QString WidgetSettings::projectPath() const {
  return m_projectPath;
}

QString WidgetSettings::localConfigPath() const {
  return m_localConfigPath;
}

QString WidgetSettings::executionDateTime() const {
  return m_executionDateTime;
}

QString WidgetSettings::executionTime() const {
  return m_executionTime;
}

WidgetSettings::WidgetSettings(const QString& groupName, WidgetSettings* parent) :
    m_groupName(groupName) {
  if (parent) {
    parent->m_widgets += this;
  }
}
