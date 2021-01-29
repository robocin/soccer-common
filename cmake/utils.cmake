set(QT5_DEFAULT_VERSION 5.15)

function(ROBOCIN_APPEND_QT5_PREFIX_PATH OUTPUT_DIRS)
  foreach(QT_PATH ${ARGN})
    if(IS_DIRECTORY ${QT_PATH})
      file(GLOB subdirs RELATIVE ${QT_PATH} ${QT_PATH}/*)
      foreach(subdir ${subdirs})
        if(IS_DIRECTORY ${QT_PATH}/${subdir}/gcc_64)
          list(APPEND DIRS_LIST ${QT_PATH}/${subdir}/gcc_64)
        endif()
      endforeach()
    endif()
  endforeach()
  set(${OUTPUT_DIRS} ${DIRS_LIST} PARENT_SCOPE)
endfunction()

macro(ROBOCIN_LINK_QT5_LIBRARIES TARGET_NAME)
  foreach(LIBRARY_NAME ${ARGN})
    ROBOCIN_APPEND_QT5_PREFIX_PATH(QT_HINT_DIRS $ENV{HOME}/Qt /opt/qt)
    find_package(Qt5 ${QT5_DEFAULT_VERSION} COMPONENTS ${LIBRARY_NAME} REQUIRED HINTS ${QT_HINT_DIRS})
    target_link_libraries(${TARGET_NAME} PUBLIC Qt5::${LIBRARY_NAME})
  endforeach()
endmacro()

function(ROBOCIN_ADD_TEST_SUBDIR TEST_NAME)
  add_subdirectory(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})
endfunction()

macro(ROBOCIN_MAKE_QT_TEST TEST_NAME)
  cmake_minimum_required(VERSION 3.13)

  project(${TEST_NAME})

  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  add_executable(${TEST_NAME} ${TEST_NAME}.h ${TEST_NAME}.cpp)

  ROBOCIN_LINK_QT5_LIBRARIES(${TEST_NAME} Test)
endmacro()

macro(ROBOCIN_LINK_AND_INCLUDE_DIR TARGET_NAME DIR_PATH)
  target_link_directories(${TARGET_NAME} PUBLIC ${DIR_PATH})
  target_include_directories(${TARGET_NAME} PUBLIC ${DIR_PATH})
endmacro()

macro(ROBOCIN_LINK_OPENGL TARGET_NAME)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)

  target_include_directories(${TARGET_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
  target_link_libraries(${TARGET_NAME} PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endmacro()

macro(ROBOCIN_LINK_FUNDAMENTAL_LIBRARIES TARGET_NAME)
  ROBOCIN_LINK_OPENGL(${TARGET_NAME})
  ROBOCIN_LINK_QT5_LIBRARIES(${TARGET_NAME} Widgets Core Gui OpenGL Concurrent Network Test Svg)
endmacro()