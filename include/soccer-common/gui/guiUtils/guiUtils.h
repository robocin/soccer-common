#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QtCore>
#include <QtWidgets>

namespace Markdown {
  inline QString bold(const QString& string) {
    return "**" + string + "**";
  }
} // namespace Markdown

#endif // GUIUTILS_H
