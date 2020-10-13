#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QRegularExpression>

namespace Utils {
  template <class T>
  QString nameOfType() {
    const QRegularExpression regex("(.*with T = )(.*)(])",
                                   QRegularExpression::NoPatternOption);
    const QRegularExpressionMatch match(regex.match(__PRETTY_FUNCTION__));
    const QStringList capturedTexts = match.capturedTexts();

    if (capturedTexts.size() == 4) {
      return capturedTexts[2];
    }

    throw std::runtime_error("capture failed.");
  }

  template <class T>
  QString nameOfTypeFromValue(const T&) {
    return nameOfType<T>();
  }
} // namespace Utils

#endif // UTILS_H
