#include "NameOfType.h"

Extends<QString> Utils::quoted(const QString& str) {
  if (str.size() > 1 && str.front() == '\"' && str.back() == '\"') {
    return str;
  }
  return "\"" + str + "\"";
}

Extends<QString> Utils::removeQuotes(const QString& str) {
  if (str.size() > 1 && str.front() == '\"' && str.back() == '\"') {
    return str.mid(1, str.size() - 2);
  }
  return str;
}

Extends<QString> Utils::removeScope(const QString& str) {
  if (auto index = str.lastIndexOf("::"); index != -1) {
    return str.mid(index + 2);
  }
  return str;
};