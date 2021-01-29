#ifndef SOCCER_COMMON_PARAMETERSHANDLER_H
#define SOCCER_COMMON_PARAMETERSHANDLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantList>
#include "soccer-common/Parameters/ParameterType/ParameterType.h"

namespace Parameters {
  bool isParameterType(const QJsonObject& object);

  class UpdateRequest {
    friend struct QtMetaTypePrivate::QMetaTypeFunctionHelper<UpdateRequest,
                                                             true>;
    UpdateRequest();

    QStringList m_path;
    QString m_value;

   public:
    UpdateRequest(const QStringList& path, const QString& value);

    QStringList path() const;
    QString value() const;
  };

  using UpdateRequests = QVector<UpdateRequest>;

  class JsonHandler {
    std::optional<QString> m_value;
    QMap<QString, JsonHandler> m_map;

   public:
    JsonHandler();
    ~JsonHandler();

    static JsonHandler fromJsonObject(const QJsonObject& object);
    void insert_or_assign(const QVector<UpdateRequest>& updates);
    void insert(const QVector<UpdateRequest>& updates);
    bool contains(const QStringList& path) const;
    QVector<UpdateRequest> updates() const;
    QByteArray toJson() const;
    QJsonObject toObject() const;
  };

  class Handler {
    std::unique_ptr<ParameterBase> value;
    std::map<QString, Handler> map;

   public:
    Q_DISABLE_COPY_MOVE(Handler);

    Handler();
    ~Handler();

    template <
        class T,
        class SFINAE = std::enable_if_t<std::is_base_of_v<ParameterBase, T>>>
    Handler& operator=(T&& p) {
      value = std::make_unique<T>(std::move(p));
      return *this;
    }

    inline Handler& operator[](const QString& p) {
      return map[p];
    }

    QByteArray json() const;
    QJsonObject jsonObject() const;
    QVector<UpdateRequest> update(const QVector<UpdateRequest>& updates);
  };
} // namespace Parameters

Q_DECLARE_METATYPE(Parameters::UpdateRequest);
Q_DECLARE_METATYPE(Parameters::UpdateRequests);

#endif // SOCCER_COMMON_PARAMETERSHANDLER_H
