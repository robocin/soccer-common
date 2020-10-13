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
    UpdateRequest(const QStringList& _path, const QString& _value) :
        m_path(_path),
        m_value(_value) {
    }

    const QStringList& path() const {
      return m_path;
    }

    const QString& value() const {
      return m_value;
    }
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

    QString dfs() const {
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
                if (ParametersHandler.value->inputType() ==
                    InputType::CheckBox) {
                  for (auto& [key, value] : ParametersHandler.map) {
                    assert(key == "true" || key == "false");
                  }
                } else if (ParametersHandler.value->inputType() ==
                           InputType::ComboBox) {

                  const QJsonDocument& doc(QJsonDocument::fromJson(
                      ("{" + ParametersHandler.value->payload() + "}")
                          .toUtf8()));
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

   public:
    ParametersHandler();
    ~ParametersHandler();

    template <class T>
    ParametersHandler& operator=(T&& p) {
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
