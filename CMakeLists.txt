cmake_minimum_required(VERSION 3.13)

set(ROBOCIN_APP "src")
set(ROBOCIN_LIB "include")

# Project type. Choose one of the two options above.
set(PROJECT_TYPE ${ROBOCIN_LIB})

if(NOT DEFINED PROJECT_TYPE)
    message(FATAL_ERROR "PROJECT_TYPE is not defined.")
endif()

# Version defines and project name.
include(version.cmake)

# Configuring project with given name.
project(${ROBOCIN_PROJECT_NAME} VERSION ${ROBOCIN_PROJECT_VERSION} LANGUAGES CXX)

if(${PROJECT_TYPE} STREQUAL ${ROBOCIN_APP})
    add_subdirectory(${ROBOCIN_APP} ${CMAKE_SOURCE_DIR}/bin)
else()
    add_subdirectory(${ROBOCIN_LIB} ${CMAKE_SOURCE_DIR}/lib)
endif()

add_subdirectory(test ${CMAKE_SOURCE_DIR}/bin/test)