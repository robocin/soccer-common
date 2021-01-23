include(${CMAKE_SOURCE_DIR}/cmake/utils.cmake)

ROBOCIN_MAKE_QT_TEST(TestUtils 5.15)
ROBOCIN_LINK_AND_INCLUDE_DIR(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE soccer-common)