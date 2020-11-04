# https://doc.qt.io/qt-5/third-party-libraries.html#library-files
unix: LIBS += -L$$PWD/../../lib -lsoccer-common

# ---------------------------------------------------------------------------- #
# The INCLUDEPATH must be one folder above. In this way you can export the     #
# project to include as:                                                       #
# #include <project-name/...>                                                  #
# ---------------------------------------------------------------------------- #
INCLUDEPATH += $$PWD/..

# src and libs files, to export. Since the INCLUDEPATH isn't adding 'src' path,
# they will be omitted.
include($$PWD/../../libs/libs.pri)
include($$PWD/../../src/src.pri)

# HEADERS that will be visible and may be included by another project.
HEADERS += $$PWD/soccer-common.h
