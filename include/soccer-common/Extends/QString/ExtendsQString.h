//
// Created by jose-cruz on 14/02/2021.
//

#ifndef SOCCER_COMMON_EXTENDSQSTRING_H
#define SOCCER_COMMON_EXTENDSQSTRING_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "google-explicit-constructor"

#include "soccer-common/Extends/Detail/ExtendsDetail.h"
#include <QString>

template <>
class Extends<QString> : public QString {
 public:
  template <class... Args>
  Extends(Args&&... args) : QString(std::forward<Args>(args)...) {
  }
  Extends(const std::string& str) : QString(QString::fromStdString(str)) {
  }

  operator std::string() const {
    return toStdString();
  }
};

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_EXTENDSQSTRING_H
