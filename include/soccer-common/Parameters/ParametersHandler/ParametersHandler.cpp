#include "ParametersHandler.h"

#include <utility>

namespace Parameters {
  bool isParameterType(const QJsonObject& object) {
    return object.contains(Detail::Value) && !object[Detail::Value].isNull() &&
           !object[Detail::Value].isObject();
  }

  // UpdateRequest
  UpdateRequest::UpdateRequest(QStringList path, QString value) :
      m_path(std::move(path)),
      m_value(std::move(value)) {
  }

  const QStringList& UpdateRequest::path() const {
    return m_path;
  }

  const QString& UpdateRequest::value() const {
    return m_value;
  }

  // JsonHandler
  JsonHandler JsonHandler::fromJsonObject(const QJsonObject& object) {
    std::function<void(JsonHandler&, const QJsonObject&)> f = [&](JsonHandler& handler,
                                                                  const QJsonObject& object) {
      if (isParameterType(object)) {
        if (object[Detail::InputType] == InputType::PushButton) {
          return;
        }
        handler.m_value = object[Detail::Value].toVariant().toString();
        if (object.contains(Detail::Conditional)) {
          f(handler, object[Detail::Conditional].toObject());
        }
      } else {
        auto keys = object.keys();
        for (const auto& key : keys) {
          f(handler.m_map[key], object[key].toObject());
        }
      }
    };
    JsonHandler handler;
    f(handler, object);
    return handler;
  }

  void JsonHandler::insert_or_assign(const QVector<UpdateRequest>& updates) {
    for (const auto& update : updates) {
      auto path = update.path();
      auto value = update.value();
      JsonHandler* ptr = this;
      for (const auto& key : path) {
        ptr = &(ptr->m_map[key]);
      }
      ptr->m_value = value;
    }
  }

  void JsonHandler::insert(const QVector<UpdateRequest>& updates) {
    for (const auto& update : updates) {
      auto path = update.path();
      auto value = update.value();
      JsonHandler* ptr = this;
      for (const auto& key : path) {
        ptr = &(ptr->m_map[key]);
      }
      if (!ptr->m_value) {
        ptr->m_value = value;
      }
    }
  }

  bool JsonHandler::contains(const QStringList& path) const {
    const JsonHandler* ptr = this;
    for (const auto& key : path) {
      if (auto it = ptr->m_map.find(key); it != ptr->m_map.end()) {
        ptr = &it.value();
      } else {
        return false;
      }
    }
    return true;
  }

  QVector<UpdateRequest> JsonHandler::updates() const {
    QVector<UpdateRequest> updates;
    std::function<void(QStringList&, const JsonHandler&)> f =
        [&f, &updates](QStringList& path, const JsonHandler& handler) {
          if (handler.m_value) {
            updates += UpdateRequest(path, handler.m_value.value());
          }
          for (auto it = handler.m_map.begin(); it != handler.m_map.end(); ++it) {
            path.push_back(it.key());
            f(path, it.value());
            path.pop_back();
          }
        };
    QStringList path;
    f(path, *this);
    return updates;
  }

  QByteArray JsonHandler::toJson() const {
    QString json;
    std::function<void(const JsonHandler&)> f = [&](const JsonHandler& handler) {
      json += "{";
      if (handler.m_value) {
        json += Utils::quoted(Detail::Value);
        json += ": ";
        json += Utils::quoted(handler.m_value.value());

        if (!handler.m_map.isEmpty()) {
          json += ", ";
          json += Utils::quoted(Detail::Conditional);
          json += ": ";
        }
      }
      if (handler.m_value && !handler.m_map.isEmpty()) {
        json += "{";
      }
      for (auto it = handler.m_map.begin(); it != handler.m_map.end(); ++it) {
        json += Utils::quoted(it.key()) + ": ";
        f(it.value());
        if (std::next(it) != handler.m_map.end()) {
          json += ", ";
        }
      }
      if (handler.m_value && !handler.m_map.isEmpty()) {
        json += "}";
      }
      json += "}";
    };
    f(*this);
    QByteArray formatted = QJsonDocument::fromJson(json.toUtf8()).toJson(QJsonDocument::Indented);
    formatted.replace(QByteArray(4, ' '), QByteArray(2, ' '));
    return formatted;
  }

  QJsonObject JsonHandler::toObject() const {
    return QJsonDocument::fromJson(toJson()).object();
  }

  // Handler
  QByteArray Handler::json() const {
    if (!value && map.empty()) {
      return "{}";
    }
    QString ret;
    std::function<void(const Handler&)> f = [&ret, &f](const Handler& parametersHandler) {
      if (parametersHandler.value) {
        ret += "{";
        //
        ret += Utils::quoted(Detail::InputType);
        ret += ": ";
        ret += Utils::quoted(parametersHandler.value->inputType());
        ret += ", ";
        //
        ret += Utils::quoted(Detail::Type);
        ret += ": ";
        ret += Utils::quoted(parametersHandler.value->type());
        ret += ", ";
        //
        ret += Utils::quoted(Detail::Description);
        ret += ": ";
        ret += Utils::quoted(parametersHandler.value->description());
        ret += ", ";
        //
        ret += Utils::quoted(Detail::Value);
        ret += ": ";
        ret += parametersHandler.value->value();
        //
        QString payload = parametersHandler.value->payload();
        if (!payload.isEmpty()) {
          ret += ", ";
        }
        ret += payload;
        //
      }

      if (!parametersHandler.map.empty()) {
        if (parametersHandler.value) {
          Q_ASSERT(parametersHandler.value->isChoosable());
          if (parametersHandler.value->inputType() == InputType::CheckBox) {
            for (auto& [key, value] : parametersHandler.map) {
              Q_ASSERT(key == "true" || key == "false");
            }
          } else if (parametersHandler.value->inputType() == InputType::ComboBox) {

            const QJsonDocument& doc(
                QJsonDocument::fromJson(("{" + parametersHandler.value->payload() + "}").toUtf8()));

            QSet<QString> keys;
            {
              const QJsonArray& jsonArray = doc.object()[Detail::Options].toArray();
              for (const auto& op : jsonArray) {
                keys += op.toVariant().toString();
              }
            }
            for (auto& [key, value] : parametersHandler.map) {
              Q_ASSERT(keys.contains(key));
            }
          }

          ret += ", " + Utils::quoted(Detail::Conditional) + ": ";
        }

        ret += "{";

        for (auto it = parametersHandler.map.begin(); it != parametersHandler.map.end(); ++it) {
          ret += Utils::quoted(it->first);
          ret += ": ";
          f(it->second);

          if (std::next(it) != parametersHandler.map.end()) {
            ret += ", ";
          }
        }

        ret += "}";
      } else {
        Q_ASSERT(parametersHandler.value);
      }

      if (parametersHandler.value) {
        ret += "}";
      }
    };
    f(*this);
    return ret.toUtf8();
  }

  QJsonObject Handler::jsonObject() const {
    return QJsonDocument::fromJson(json()).object();
  }

  QVector<UpdateRequest> Handler::update(const QVector<UpdateRequest>& updates,
                                         QVector<ParameterBase*>* updated) {
    QVector<UpdateRequest> notUpdated;
    for (const auto& up : updates) {
      auto path = up.path();
      Handler* ptr = this;
      bool found = true;
      for (const auto& key : path) {
        if (ptr->map.find(key) != ptr->map.end()) {
          ptr = &(ptr->map[key]);
        } else {
          found = false;
          break;
        }
      }
      if (found && ptr->value) {
        if (ptr->value->update(up.value())) {
          if (updated) {
            updated->emplace_back(ptr->value.get());
          }
        } else {
          notUpdated += up;
        }
      } else {
        notUpdated += up;
      }
    }
    return notUpdated;
  }
} // namespace Parameters

static_block {
  qRegisterMetaType<Parameters::UpdateRequest>();
  qRegisterMetaType<Parameters::UpdateRequests>();
};
