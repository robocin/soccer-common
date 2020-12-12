#include "ParametersHandler.h"

namespace Parameters {
  UpdateRequest::UpdateRequest(const QStringList& path, const QString& value) :
      m_path(path),
      m_value(value) {
  }

  QStringList UpdateRequest::path() const {
    return m_path;
  }

  QString UpdateRequest::value() const {
    return m_value;
  }

  QString Handler::dfs() const {
    QString ret;
    std::function<void(const Handler&)> f =
        [&ret, &f](const Handler& parametersHandler) {
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
              assert(parametersHandler.value->isChooseable());
              if (parametersHandler.value->inputType() == InputType::CheckBox) {
                for (auto& [key, value] : parametersHandler.map) {
                  assert(key == "true" || key == "false");
                }
              } else if (parametersHandler.value->inputType() ==
                         InputType::ComboBox) {

                const QJsonDocument& doc(QJsonDocument::fromJson(
                    ("{" + parametersHandler.value->payload() + "}").toUtf8()));
                const QVariantList& variantList =
                    doc.object()[Detail::Options].toArray().toVariantList();

                for (auto& [key, value] : parametersHandler.map) {
                  bool can = false;
                  for (const auto& op : variantList) {
                    if (key == op.toString()) {
                      can = true;
                    }
                  }
                  assert(can);
                }
              }

              ret += ", " + Utils::quoted(Detail::Conditional) + ": ";
            }

            ret += "{";

            for (auto it = parametersHandler.map.begin();
                 it != parametersHandler.map.end();
                 ++it) {
              ret += Utils::quoted(it->first);
              ret += ": ";
              f(it->second);

              if (std::next(it) != parametersHandler.map.end()) {
                ret += ", ";
              }
            }

            ret += "}";
          } else {
            assert(parametersHandler.value);
          }

          if (parametersHandler.value) {
            ret += "}";
          }
        };
    f(*this);
    return ret;
  }

  Handler::Handler() : value(nullptr) {
  }

  Handler::~Handler() {
    if (value != nullptr) {
      delete value;
    }
    value = nullptr;
  }

  QString Handler::json() const {
    return dfs();
  }

  QJsonObject Handler::jsonObject() const {
    return QJsonDocument::fromJson(dfs().toUtf8()).object();
  }

  QVector<UpdateRequest>
  Handler::update(const QVector<UpdateRequest>& updates) {
    QVector<UpdateRequest> ret;
    for (const auto& up : updates) {
      auto path = up.path();
      Handler* ptr = this;
      bool notFound = false;
      for (auto key : path) {
        if (ptr->map.find(key) != ptr->map.end()) {
          ptr = &(ptr->map[key]);
        } else {
          notFound = true;
          break;
        }
      }
      if (notFound) {
        ret += up;
      } else if (ptr->value) {
        if (!ptr->value->update(up.value())) {
          ret += up;
        }
      } else {
        ret += up;
      }
    }
    return ret;
  }
} // namespace Parameters
