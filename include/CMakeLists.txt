cmake_minimum_required(VERSION 3.16)

include(${CMAKE_CURRENT_SOURCE_DIR}/../version.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/utils.cmake)

PROJECT(soccer-common LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModulesPrivate/ModulesPrivate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Entities.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Robot/Robot.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Ball/Ball.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Entity/Entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/ParametersHandler/ParametersHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/Parameters.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/ParameterType/ParameterType.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/soccer-common.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/gui.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParameterWidget/ParameterWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParametersDialog/ParametersDialog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/SmartVerticalFlowLayout/SmartVerticalFlowLayout.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ScoreboardWidget/ScoreboardWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/DynamicFontSizeQLabel/DynamicFontSizeQLabel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParametersWindow/ParametersWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ColorTeamWidget/ColorTeamWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/AttackSideWidget/AttackSideWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ScrollAreaForFlowLayout/ScrollAreaForFlowLayout.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ModuleBox/ModuleBox.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/InputWidgets/InputWidgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/Widgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/PlayPauseWidget/PlayPauseWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/Interfaces.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/MenuBarOptions/MenuBarOptions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/ModulesWidgets/ModulesWidgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/WidgetSettings/WidgetSettings.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/VisualizationWidget/VisualizationWidget.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/InfoWidgets/InfoWidgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/RobotsWidgets/RobotsWidgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/MainWindow/MainWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/AbstractWidgets/AbstractWidgets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/AbstractWidgets/ParametersDialogBase/ParametersDialogBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/guiFactory/guiFactory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GameVisualizerPainter2D/GameVisualizerPainter2D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GameVisualizer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/Painting/Painting.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLGameVisualizerCore_2_1/GLGameVisualizerCore_2_1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLTessellatorHelper_2_1/GLTessellatorHelper_2_1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLTextHelper_2_1/GLTextHelper_2_1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/guiUtils/guiUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Field/Field.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/ExtendsPoint/ExtendsPoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/detail/ExtendsImpl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/Extends.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModuleBase/ModulePrivate/ModulePrivate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModuleBase/ModuleBase.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/InterruptRequest/InterruptRequest.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/StaticBlockTag/StaticBlockTag.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/PtrMulticast/PtrMulticast.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Singleton/Singleton.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SharedWrapper/SharedWrapper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/StringHelper/StringHelper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Regex/Regex.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/InheritanceFactorySafeMap/InheritanceFactorySafeMap.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Color/Color.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SharedOptional/SharedOptional.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SetterGetter/SetterGetter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Geometry/Geometry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/MagicEnum/MagicEnum.h
        )

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModulesPrivate/ModulesPrivate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Robot/Robot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Ball/Ball.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Entity/Entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Entities/Entities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/ParametersHandler/ParametersHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/ParameterType/ParameterType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Parameters/Parameters.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParameterWidget/ParameterWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParametersDialog/ParametersDialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/SmartVerticalFlowLayout/SmartVerticalFlowLayout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ScoreboardWidget/ScoreboardWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/DynamicFontSizeQLabel/DynamicFontSizeQLabel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ParametersWindow/ParametersWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ColorTeamWidget/ColorTeamWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/AttackSideWidget/AttackSideWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ScrollAreaForFlowLayout/ScrollAreaForFlowLayout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/ModuleBox/ModuleBox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/InputWidgets/InputWidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Widgets/PlayPauseWidget/PlayPauseWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/MenuBarOptions/MenuBarOptions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/Interfaces.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/ModulesWidgets/ModulesWidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/WidgetSettings/WidgetSettings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/VisualizationWidget/VisualizationWidget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/InfoWidgets/InfoWidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/Interfaces/RobotsWidgets/RobotsWidgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/MainWindow/MainWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/AbstractWidgets/ParametersDialogBase/ParametersDialogBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/guiFactory/guiFactory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GameVisualizerPainter2D/GameVisualizerPainter2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/Painting/Painting.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLGameVisualizerCore_2_1/GLGameVisualizerCore_2_1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLTessellatorHelper_2_1/GLTessellatorHelper_2_1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GameVisualizer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/GameVisualizer/GLTextHelper_2_1/GLTextHelper_2_1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/gui/guiUtils/guiUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Field/Field.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/ExtendsPoint/ExtendsPoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/Extends.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Extends/detail/ExtendsImpl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModuleBase/ModulePrivate/ModulePrivate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/ModuleBase/ModuleBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/InterruptRequest/InterruptRequest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/StaticBlockTag/StaticBlockTag.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/PtrMulticast/PtrMulticast.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Singleton/Singleton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SharedWrapper/SharedWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/StringHelper/StringHelper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Regex/Regex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/InheritanceFactorySafeMap/InheritanceFactorySafeMap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/Color/Color.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SharedOptional/SharedOptional.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Utils/SetterGetter/SetterGetter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/Geometry/Geometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/soccer-common/MagicEnum/MagicEnum.cpp
        )

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/magic_enum/include)
ADD_QT5_LIBRARIES(5.15 ${PROJECT_NAME} Widgets Core Gui OpenGL Concurrent Network)