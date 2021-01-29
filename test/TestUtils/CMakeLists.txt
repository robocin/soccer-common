include(${CMAKE_SOURCE_DIR}/cmake/utils.cmake)

ROBOCIN_MAKE_QT_TEST(TestUtils)
ROBOCIN_LINK_AND_INCLUDE_DIR(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE soccer-common)