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
  Extends() = default;
  Extends(const QChar* unicode, qsizetype size) : QString(unicode, size) {
  }
  Extends(const QChar& c) : QString(c) {
  }
  Extends(qsizetype size, const QChar& c) : QString(size, c) {
  }
  Extends(const QLatin1String& latin1) : QString(latin1) {
  }
  Extends(const QString& other) : QString(other) {
  }
  Extends(QString&& other) : QString(other) {
  }
  Extends(const char* ch) : QString(ch) {
  }
  Extends(const QByteArray& a) : QString(a) {
  }
  Extends(qsizetype size, Qt::Initialization initialization) : QString(size, initialization) {
  }
  Extends(const std::string& str) : QString(QString::fromStdString(str)) {
  }
};

#pragma clang diagnostic pop

#endif // SOCCER_COMMON_EXTENDSQSTRING_H
