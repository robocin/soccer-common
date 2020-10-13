#include "ParametersHandler.h"

namespace Parameters {
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
