#ifndef SOCCER_COMMON_PARAMETERSHANDLER_H
#define SOCCER_COMMON_PARAMETERSHANDLER_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"

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
    UpdateRequest() = default;
    UpdateRequest(QStringList path, QString value);

    const QStringList& path() const;
    const QString& value() const;
  };

  using UpdateRequests = QVector<UpdateRequest>;

  class JsonHandler {
    std::optional<QString> m_value;
    QMap<QString, JsonHandler> m_map;

   public:
    JsonHandler() = default;
    ~JsonHandler() = default;

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
    Q_DISABLE_COPY(Handler);

    Handler() = default;
    ~Handler() = default;

    Handler& operator=(Handler&& other) = default;

    template <class T, std::enable_if_t<std::is_base_of_v<ParameterBase, T>, bool> = true>
    Handler& operator=(T&& p) {
      value = std::make_unique<T>(std::forward<T>(p));
      return *this;
    }

    inline Handler& operator[](const QString& p) {
      return map[p];
    }

    QByteArray json() const;
    QJsonObject jsonObject() const;
    QVector<UpdateRequest> update(const QVector<UpdateRequest>& updates,
                                  QVector<ParameterBase*>* updated = nullptr);
    bool empty() const;
  };
} // namespace Parameters

Q_DECLARE_METATYPE(Parameters::UpdateRequest);
Q_DECLARE_METATYPE(Parameters::UpdateRequests);

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_PARAMETERSHANDLER_H