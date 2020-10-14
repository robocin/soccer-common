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
        [&ret, &f](const ParametersHandler& ParametersHandler) {
          if (ParametersHandler.value) {
            ret += "{";
            //
            ret += Utils::quoted(Detail::InputType);
            ret += ": ";
            ret += Utils::quoted(ParametersHandler.value->inputType());
            ret += ", ";
            //
            ret += Utils::quoted(Detail::Type);
            ret += ": ";
            ret += Utils::quoted(ParametersHandler.value->type());
            ret += ", ";
            //
            ret += Utils::quoted(Detail::Description);
            ret += ": ";
            ret += Utils::quoted(ParametersHandler.value->description());
            ret += ", ";
            //
            ret += Utils::quoted(Detail::Value);
            ret += ": ";
            ret += ParametersHandler.value->value();
            //
            QString payload = ParametersHandler.value->payload();
            if (!payload.isEmpty()) {
              ret += ", ";
            }
            ret += payload;
            //
          }

          if (!ParametersHandler.map.empty()) {
            if (ParametersHandler.value) {
              assert(ParametersHandler.value->isChooseable());
              if (ParametersHandler.value->inputType() == InputType::CheckBox) {
                for (auto& [key, value] : ParametersHandler.map) {
                  assert(key == "true" || key == "false");
                }
              } else if (ParametersHandler.value->inputType() ==
                         InputType::ComboBox) {

                const QJsonDocument& doc(QJsonDocument::fromJson(
                    ("{" + ParametersHandler.value->payload() + "}").toUtf8()));
                const QVariantList& variantList =
                    doc.object()[Detail::Options].toArray().toVariantList();

                for (auto& [key, value] : ParametersHandler.map) {
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

            for (auto it = ParametersHandler.map.begin();
                 it != ParametersHandler.map.end();
                 ++it) {
              auto& [first, second] = *it;
              ret += Utils::quoted(first);
              ret += ": ";
              f(second);

              if (std::next(it) != ParametersHandler.map.end()) {
                ret += ", ";
              }
            }

            ret += "}";
          } else {
            assert(ParametersHandler.value);
          }

          if (ParametersHandler.value) {
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

  QJsonDocument ParametersHandler::jsonDocument() const {
    return QJsonDocument::fromJson(json().toUtf8());
  }

  void ParametersHandler::update(const QVector<UpdateRequest>& updates) {
    for (const auto& up : updates) {
      auto path = up.path();
      ParametersHandler* ptr = this;
      for (auto key : path) {
        if (ptr->map.find(key) != ptr->map.end()) {
          ptr = &(ptr->map[key]);
        } else {
          throw std::runtime_error("key not found.");
        }
      }
      if (ptr->value) {
        ptr->value->update(up.value());
      } else {
        throw std::runtime_error("parameter to update not found.");
      }
    }
  }
} // namespace Parameters
