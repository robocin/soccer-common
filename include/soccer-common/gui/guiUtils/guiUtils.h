#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QtCore>
#include <QtWidgets>
#include "soccer-common/Utils/Utils.h"

template <class... Args>
using QWidgetWith = PtrMulticast<QWidget, Args...>;

namespace Markdown {
  inline QString bold(const QString& string) {
    return "**" + string + "**";
  }
} // namespace Markdown

#endif // GUIUTILS_H
