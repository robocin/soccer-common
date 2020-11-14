#include "ParametersHandler.h"

namespace Parameters {
  UpdateRequest::UpdateRequest(const QStringList& _path,
                               const QString& _value) :
      m_path(_path),
      m_value(_value) {
  }

  const QStringList& UpdateRequest::path() const {
    return m_path;
  }

  const QString& UpdateRequest::value() const {
    return m_value;
  }

  QString ParametersHandler::dfs() const {
    QString ret;
    std::function<void(const ParametersHandler&)> f =
        [&ret, &f](const ParametersHandler& parametersHandler) {
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

  ParametersHandler::ParametersHandler() : value(nullptr) {
  }

  ParametersHandler::~ParametersHandler() {
    if (value != nullptr) {
      delete value;
    }
    value = nullptr;
  }

  QString ParametersHandler::json() const {
    return dfs();
  }

  QVector<UpdateRequest>
  ParametersHandler::update(const QVector<UpdateRequest>& updates) {
    QVector<UpdateRequest> ret;
    for (const auto& up : updates) {
      auto path = up.path();
      ParametersHandler* ptr = this;
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
