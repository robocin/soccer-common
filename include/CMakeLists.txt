cmake_minimum_required(VERSION 3.16)

include(../version.cmake)
include(../cmake/utils.cmake)

project(${ROBOCIN_PROJECT_NAME} VERSION ${ROBOCIN_PROJECT_VERSION} LANGUAGES CXX)

include_directories(${CMAKE_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "*.h" "*.hh" "*.h++" "*.hxx" "*.H" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.c" "*.cc" "*.c++" "*.cxx" "*.C" "*.cpp")

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

get_filename_component(PROJECT_PATH ../ ABSOLUTE)
ROBOCIN_LINK_PROJECT_DEFINITIONS(${PROJECT_NAME} ${PROJECT_PATH})
ROBOCIN_LINK_FUNDAMENTAL_LIBRARIES(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ../libs/magic_enum/include)

ROBOCIN_DOXYGEN_CUSTOM_TARGET(${PROJECT_NAME}-documentation ../)
