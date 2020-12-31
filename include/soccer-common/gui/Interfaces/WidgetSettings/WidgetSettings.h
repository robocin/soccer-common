#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/Utils/Utils.h"

class WidgetSettings {
  QString m_groupName;
  QList<WidgetSettings*> m_widgets;

  QString m_projectName;
  QString m_projectVersion;
  QString m_projectPath;
  QString m_localConfigPath;
  QString m_executionDateTime;
  QString m_executionTime;

 protected:
  virtual void writeLocalSettings(QSettings& settings) = 0;
  virtual void loadLocalSettings(const QSettings& settings) = 0;

  virtual void writeLocalSettings(QJsonObject& json);
  virtual void loadLocalSettings(const QJsonObject& json);

  void writeSettings(QSettings& settings, QJsonObject& json);
  void loadSettings(QSettings& settings, QJsonObject& json);

  void setupWidgetSettings(const QString& projectName,
                           const QString& projectVersion,
                           const QString& projectPath,
                           const QString& localConfigPath,
                           const QString& executionDateTime,
                           const QString& executionTime);

  QString projectName() const;
  QString projectVersion() const;
  QString projectPath() const;
  QString localConfigPath() const;
  QString executionDateTime() const;
  QString executionTime() const;

 public:
  explicit WidgetSettings(const QString& groupName,
                          WidgetSettings* parent = nullptr);

  template <class T>
  explicit WidgetSettings(const T* widget, WidgetSettings* parent = nullptr) :
      WidgetSettings(Utils::nameOfType<T>(), parent) {
    Q_ASSERT(static_cast<const WidgetSettings*>(widget) ==
             static_cast<const WidgetSettings*>(this));
  }
};

#endif // WIDGETSETTINGS_H
