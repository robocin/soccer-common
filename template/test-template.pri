# ---------------------------------------------------------------------------- #
# Just paste this code in your 'test-name.pro' and add 'test-name.(h | cpp)'   #
# WARNING: You may need to adjust the relative paths.                          #
#                                                                              #
# You can learn how to create a unity-test here:                               #
# https://doc.qt.io/qt-5/qtest-tutorial.html                                   #
# ---------------------------------------------------------------------------- #

# Includes must contain the necessary relative includepaths.
include($$PWD/../../template/template.pri)
include($$PWD/../../libs/libs.pri)

INCLUDEPATH += $$PWD/../../src
include($$PWD/../../src/src.pri)

# Putting the binary in the root of project, specific for testing.
DESTDIR = $$PWD/../../bin/test # bin, because tests are executable files in Qt.

TARGET # The binary will remain with the name of the project, as it is the same name as the test.

TEMPLATE = app
QT += testlib

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
