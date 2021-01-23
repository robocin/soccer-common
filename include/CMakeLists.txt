cmake_minimum_required(VERSION 3.13)

include(../version.cmake)
include(../cmake/utils.cmake)

PROJECT(soccer-common LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_FILES
        soccer-common/ModulesPrivate/ModulesPrivate.h
        soccer-common/Entities/Entities.h
        soccer-common/Entities/Robot/Robot.h
        soccer-common/Entities/Ball/Ball.h
        soccer-common/Entities/Entity/Entity.h
        soccer-common/Parameters/ParametersHandler/ParametersHandler.h
        soccer-common/Parameters/Parameters.h
        soccer-common/Parameters/ParameterType/ParameterType.h
        soccer-common/soccer-common.h
        soccer-common/gui/gui.h
        soccer-common/gui/Widgets/ParameterWidget/ParameterWidget.h
        soccer-common/gui/Widgets/ParametersDialog/ParametersDialog.h
        soccer-common/gui/Widgets/SmartVerticalFlowLayout/SmartVerticalFlowLayout.h
        soccer-common/gui/Widgets/ScoreboardWidget/ScoreboardWidget.h
        soccer-common/gui/Widgets/DynamicFontSizeQLabel/DynamicFontSizeQLabel.h
        soccer-common/gui/Widgets/ParametersWindow/ParametersWindow.h
        soccer-common/gui/Widgets/ColorTeamWidget/ColorTeamWidget.h
        soccer-common/gui/Widgets/AttackSideWidget/AttackSideWidget.h
        soccer-common/gui/Widgets/ScrollAreaForFlowLayout/ScrollAreaForFlowLayout.h
        soccer-common/gui/Widgets/ModuleBox/ModuleBox.h
        soccer-common/gui/Widgets/InputWidgets/InputWidgets.h
        soccer-common/gui/Widgets/Widgets.h
        soccer-common/gui/Widgets/PlayPauseWidget/PlayPauseWidget.h
        soccer-common/gui/Interfaces/Interfaces.h
        soccer-common/gui/Interfaces/MenuBarOptions/MenuBarOptions.h
        soccer-common/gui/Interfaces/ModulesWidgets/ModulesWidgets.h
        soccer-common/gui/Interfaces/WidgetSettings/WidgetSettings.h
        soccer-common/gui/Interfaces/VisualizationWidget/VisualizationWidget.h
        soccer-common/gui/Interfaces/InfoWidgets/InfoWidgets.h
        soccer-common/gui/Interfaces/RobotsWidgets/RobotsWidgets.h
        soccer-common/gui/MainWindow/MainWindow.h
        soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.h
        soccer-common/gui/AbstractWidgets/AbstractWidgets.h
        soccer-common/gui/AbstractWidgets/ParametersDialogBase/ParametersDialogBase.h
        soccer-common/gui/guiFactory/guiFactory.h
        soccer-common/gui/GameVisualizer/GameVisualizerPainter2D/GameVisualizerPainter2D.h
        soccer-common/gui/GameVisualizer/GameVisualizer.h
        soccer-common/gui/GameVisualizer/Painting/Painting.h
        soccer-common/gui/GameVisualizer/GLGameVisualizerCore_2_1/GLGameVisualizerCore_2_1.h
        soccer-common/gui/GameVisualizer/GLTessellatorHelper_2_1/GLTessellatorHelper_2_1.h
        soccer-common/gui/GameVisualizer/GLTextHelper_2_1/GLTextHelper_2_1.h
        soccer-common/gui/guiUtils/guiUtils.h
        soccer-common/Field/Field.h
        soccer-common/Extends/ExtendsPoint/ExtendsPoint.h
        soccer-common/Extends/detail/ExtendsImpl.h
        soccer-common/Extends/Extends.h
        soccer-common/ModuleBase/ModulePrivate/ModulePrivate.h
        soccer-common/ModuleBase/ModuleBase.h
        soccer-common/Utils/InterruptRequest/InterruptRequest.h
        soccer-common/Utils/StaticBlockTag/StaticBlockTag.h
        soccer-common/Utils/PtrMulticast/PtrMulticast.h
        soccer-common/Utils/Singleton/Singleton.h
        soccer-common/Utils/SharedWrapper/SharedWrapper.h
        soccer-common/Utils/StringHelper/StringHelper.h
        soccer-common/Utils/Utils.h
        soccer-common/Utils/Regex/Regex.h
        soccer-common/Utils/InheritanceFactorySafeMap/InheritanceFactorySafeMap.h
        soccer-common/Utils/Color/Color.h
        soccer-common/Utils/SharedOptional/SharedOptional.h
        soccer-common/Utils/SetterGetter/SetterGetter.h
        soccer-common/Geometry/Geometry.h
        soccer-common/MagicEnum/MagicEnum.h
        )

set(SOURCE_FILES
        soccer-common/ModulesPrivate/ModulesPrivate.cpp
        soccer-common/Entities/Robot/Robot.cpp
        soccer-common/Entities/Ball/Ball.cpp
        soccer-common/Entities/Entity/Entity.cpp
        soccer-common/Entities/Entities.cpp
        soccer-common/Parameters/ParametersHandler/ParametersHandler.cpp
        soccer-common/Parameters/ParameterType/ParameterType.cpp
        soccer-common/Parameters/Parameters.cpp
        soccer-common/gui/Widgets/ParameterWidget/ParameterWidget.cpp
        soccer-common/gui/Widgets/ParametersDialog/ParametersDialog.cpp
        soccer-common/gui/Widgets/SmartVerticalFlowLayout/SmartVerticalFlowLayout.cpp
        soccer-common/gui/Widgets/ScoreboardWidget/ScoreboardWidget.cpp
        soccer-common/gui/Widgets/DynamicFontSizeQLabel/DynamicFontSizeQLabel.cpp
        soccer-common/gui/Widgets/ParametersWindow/ParametersWindow.cpp
        soccer-common/gui/Widgets/ColorTeamWidget/ColorTeamWidget.cpp
        soccer-common/gui/Widgets/AttackSideWidget/AttackSideWidget.cpp
        soccer-common/gui/Widgets/ScrollAreaForFlowLayout/ScrollAreaForFlowLayout.cpp
        soccer-common/gui/Widgets/ModuleBox/ModuleBox.cpp
        soccer-common/gui/Widgets/InputWidgets/InputWidgets.cpp
        soccer-common/gui/Widgets/PlayPauseWidget/PlayPauseWidget.cpp
        soccer-common/gui/Interfaces/MenuBarOptions/MenuBarOptions.cpp
        soccer-common/gui/Interfaces/Interfaces.cpp
        soccer-common/gui/Interfaces/ModulesWidgets/ModulesWidgets.cpp
        soccer-common/gui/Interfaces/WidgetSettings/WidgetSettings.cpp
        soccer-common/gui/Interfaces/VisualizationWidget/VisualizationWidget.cpp
        soccer-common/gui/Interfaces/InfoWidgets/InfoWidgets.cpp
        soccer-common/gui/Interfaces/RobotsWidgets/RobotsWidgets.cpp
        soccer-common/gui/MainWindow/MainWindowMenuBar/MainWindowMenuBar.cpp
        soccer-common/gui/MainWindow/MainWindow.cpp
        soccer-common/gui/AbstractWidgets/ParametersDialogBase/ParametersDialogBase.cpp
        soccer-common/gui/guiFactory/guiFactory.cpp
        soccer-common/gui/GameVisualizer/GameVisualizerPainter2D/GameVisualizerPainter2D.cpp
        soccer-common/gui/GameVisualizer/Painting/Painting.cpp
        soccer-common/gui/GameVisualizer/GLGameVisualizerCore_2_1/GLGameVisualizerCore_2_1.cpp
        soccer-common/gui/GameVisualizer/GLTessellatorHelper_2_1/GLTessellatorHelper_2_1.cpp
        soccer-common/gui/GameVisualizer/GameVisualizer.cpp
        soccer-common/gui/GameVisualizer/GLTextHelper_2_1/GLTextHelper_2_1.cpp
        soccer-common/gui/guiUtils/guiUtils.cpp
        soccer-common/Field/Field.cpp
        soccer-common/Extends/ExtendsPoint/ExtendsPoint.cpp
        soccer-common/Extends/Extends.cpp
        soccer-common/Extends/detail/ExtendsImpl.cpp
        soccer-common/ModuleBase/ModulePrivate/ModulePrivate.cpp
        soccer-common/ModuleBase/ModuleBase.cpp
        soccer-common/Utils/InterruptRequest/InterruptRequest.cpp
        soccer-common/Utils/Utils.cpp
        soccer-common/Utils/StaticBlockTag/StaticBlockTag.cpp
        soccer-common/Utils/PtrMulticast/PtrMulticast.cpp
        soccer-common/Utils/Singleton/Singleton.cpp
        soccer-common/Utils/SharedWrapper/SharedWrapper.cpp
        soccer-common/Utils/StringHelper/StringHelper.cpp
        soccer-common/Utils/Regex/Regex.cpp
        soccer-common/Utils/InheritanceFactorySafeMap/InheritanceFactorySafeMap.cpp
        soccer-common/Utils/Color/Color.cpp
        soccer-common/Utils/SharedOptional/SharedOptional.cpp
        soccer-common/Utils/SetterGetter/SetterGetter.cpp
        soccer-common/Geometry/Geometry.cpp
        soccer-common/MagicEnum/MagicEnum.cpp
        )

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

ROBOCIN_ADD_PROJECT_DEFINITIONS(soccer-common)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(soccer-common PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


target_include_directories(${PROJECT_NAME} PUBLIC ../libs/magic_enum/include)
ROBOCIN_ADD_QT5_LIBRARIES(5.15 ${PROJECT_NAME} Widgets Core Gui OpenGL Concurrent Network)
