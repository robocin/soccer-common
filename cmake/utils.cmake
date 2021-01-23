macro(ROBOCIN_ADD_QT5_LIBRARIES QT_VERSION TARGET_NAME)
  foreach(LIBRARY_NAME ${ARGN})
    find_package(Qt5 ${QT_VERSION} COMPONENTS ${LIBRARY_NAME} REQUIRED)
    target_link_libraries(${TARGET_NAME} PUBLIC Qt5::${LIBRARY_NAME})
  endforeach()
endmacro()

macro(ROBOCIN_ADD_TEST_SUBDIR TEST_NAME)
  add_subdirectory(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})
endmacro()

macro(ROBOCIN_MAKE_QT_TEST TEST_NAME QT_VERSION)
  cmake_minimum_required(VERSION 3.13)

  project(${TEST_NAME})

  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  add_executable(${TEST_NAME} ${TEST_NAME}.h ${TEST_NAME}.cpp)

  ROBOCIN_ADD_QT5_LIBRARIES(${QT_VERSION} ${TEST_NAME} Test)
endmacro()

macro(ROBOCIN_LINK_AND_INCLUDE_DIR DIR_PATH)
  link_directories(${DIR_PATH})
  include_directories(${DIR_PATH})
endmacro()