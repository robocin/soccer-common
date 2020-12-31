#ifndef INTERFACES_H
#define INTERFACES_H

#include "WidgetSettings/WidgetSettings.h"
#include "MenuBarOptions/MenuBarOptions.h"
#include "InfoWidgets/InfoWidgets.h"
#include "ModulesWidgets/ModulesWidgets.h"
#include "VisualizationWidget/VisualizationWidget.h"

template <class... Args>
using QWidgetWith = PtrMulticast<QWidget, Args...>;

#endif // INTERFACES_H
