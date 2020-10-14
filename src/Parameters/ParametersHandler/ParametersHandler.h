#ifndef PARAMETERSHANDLER_H
#define PARAMETERSHANDLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantList>
#include "Parameters/ParameterType/ParameterType.h"

namespace Parameters {
  class UpdateRequest {
    QStringList m_path;
    QString m_value;

   public:
    UpdateRequest(const QStringList& _path, const QString& _value);

    const QStringList& path() const;
    const QString& value() const;
  };

  class ParametersHandler {
    ParameterBase* value;
    std::map<QString, ParametersHandler> map;

    // disable_copy:
    ParametersHandler(const ParametersHandler&) = delete;
    ParametersHandler& operator=(const ParametersHandler&) = delete;

    // disable_move:
    ParametersHandler(ParametersHandler&&) = delete;
    ParametersHandler& operator=(ParametersHandler&&) = delete;

    QString dfs() const;

   public:
    ParametersHandler();
    ~ParametersHandler();

    template <class T>
    ParametersHandler& operator=(T&& p) {
      static_assert(std::is_base_of_v<ParameterBase, T>);
      if (value) {
        delete value;
      }
      value = new T(p);
      return *this;
    }

    inline ParametersHandler& operator[](const QString& p) {
      return map[p];
    }

    QString json() const;
    QJsonDocument jsonDocument() const;

    void update(const QVector<UpdateRequest>& updates);
  };
} // namespace Parameters

#endif // PARAMETERSHANDLER_H
