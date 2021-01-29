cmake_minimum_required(VERSION 3.13)

include(../cmake-common/robocin.cmake)

ROBOCIN_ADD_TEST_SUBDIR(TestGeometry)
ROBOCIN_ADD_TEST_SUBDIR(TestMagicEnum)
ROBOCIN_ADD_TEST_SUBDIR(TestParameters)
ROBOCIN_ADD_TEST_SUBDIR(TestUtils)
