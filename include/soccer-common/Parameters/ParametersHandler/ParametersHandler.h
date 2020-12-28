#ifndef PARAMETERSHANDLER_H
#define PARAMETERSHANDLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantList>
#include "soccer-common/Parameters/ParameterType/ParameterType.h"

namespace Parameters {
  bool isParameterType(const QJsonObject& object);

  class UpdateRequest {
    QStringList m_path;
    QString m_value;

   public:
    UpdateRequest(const QStringList& path, const QString& value);

    QStringList path() const;
    QString value() const;
  };

  class JsonHandler {
    std::optional<QString> m_value;
    QMap<QString, JsonHandler> m_map;

   public:
    JsonHandler();
    ~JsonHandler();

    static JsonHandler fromJsonObject(const QJsonObject& object);
    void update(const QVector<UpdateRequest>& updates);
    QVector<UpdateRequest> get() const;
    QByteArray toJson() const;
  };

  class Handler {
    std::unique_ptr<ParameterBase> value;
    std::map<QString, Handler> map;

   public:
    Q_DISABLE_COPY_MOVE(Handler);

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

    void clear();
    QByteArray json() const;
    QJsonObject jsonObject() const;
    QVector<UpdateRequest> update(const QVector<UpdateRequest>& updates);
  };
} // namespace Parameters

#endif // PARAMETERSHANDLER_H
