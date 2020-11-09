#include "Utils.h"

QString Utils::quoted(const QString& str) {
  if (str.size() > 1 && str.front() == '\"' && str.back() == '\"') {
    return str;
  }
  return "\"" + str + "\"";
}

QString Utils::removeQuotes(const QString& str) {
  if (str.size() > 1 && str.front() == '\"' && str.back() == '\"') {
    return str.mid(1, str.size() - 2);
  }
  return str;
}
