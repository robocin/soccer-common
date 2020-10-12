TEMPLATE = subdirs

include($$PWD/../version.pri)

# ---------------------------------------------------------------------------- #
# Please, read this documentation:                                             #
# https://doc.qt.io/qt-5/third-party-libraries.html                            #
#                                                                              #
# The idea is to put everything you need to export in the '.pri' file, to      #
# include it in another project, without further complications.                #
# ---------------------------------------------------------------------------- #

!exists($$PWD/$${PROJECT_NAME}/$${PROJECT_NAME}.pri) {
  message(To export the library to other projects, you must create a '.pri' file with the name of the project, which contains HEADERS, SOURCES, INCLUDEPATHs and LIBS, with their relative paths (PWD), inside a folder with the name of the project, in the current directory.)
} else {
  HEADERS += $$files($$PWD/$${PROJECT_NAME}/*.h, true)

  SOURCES += $$files($$PWD/$${PROJECT_NAME}/*.cpp, true)

  DISTFILES = $$PWD/$${PROJECT_NAME}/$${PROJECT_NAME}.pri
}
