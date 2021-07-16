cmake_minimum_required(VERSION 3.16)

# Version defines and project name.
include(version.cmake)

# Configuring project with given name.
project(${ROBOCIN_PROJECT_NAME} VERSION ${ROBOCIN_PROJECT_VERSION} LANGUAGES CXX)

# adds library subdir and tests subdir.
add_subdirectory(include ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(test ${CMAKE_CURRENT_SOURCE_DIR}/bin/test)
