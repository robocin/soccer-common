cmake_minimum_required(VERSION 3.13)

# Version defines and project name.
include(version.cmake)

# Configuring project with given name.
project(${ROBOCIN_PROJECT_NAME} VERSION ${ROBOCIN_PROJECT_VERSION} LANGUAGES CXX)

# adds library subdir and tests subdir.
add_subdirectory(include ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(test ${CMAKE_SOURCE_DIR}/bin/test)