#ifndef PARAMETERSHANDLER_H
#define PARAMETERSHANDLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantList>
#include "soccer-common/Parameters/ParameterType/ParameterType.h"

namespace Parameters {
  class UpdateRequest {
    QStringList m_path;
    QString m_value;

   public:
    UpdateRequest(const QStringList& path, const QString& value);

    QStringList path() const;
    QString value() const;
  };

  class Handler {
    std::unique_ptr<ParameterBase> value;
    std::map<QString, Handler> map;

    // disable_copy:
    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    // disable_move:
    Handler(Handler&&) = delete;
    Handler& operator=(Handler&&) = delete;

    QString dfs() const;

   public:
    Handler();
    ~Handler();

    template <class T>
    Handler& operator=(T&& p) {
      static_assert(std::is_base_of_v<ParameterBase, T>);
      value = std::make_unique<T>(std::move(p));
      return *this;
    }

    inline Handler& operator[](const QString& p) {
      return map[p];
    }

    QString json() const;
    QJsonObject jsonObject() const;

    QVector<UpdateRequest> update(const QVector<UpdateRequest>& updates);
  };
} // namespace Parameters

#endif // PARAMETERSHANDLER_H
