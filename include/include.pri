include($$PWD/../version.pri)

!exists($$PWD/$${PROJECT_NAME}/$${PROJECT_NAME}.pri) {
  message("To export the library to other projects, you must create a '.pri' file with the name of the project, which contains HEADERS, SOURCES, INCLUDEPATHs and LIBS, with their relative paths ($$PWD), inside a folder with the name of the project, in the current directory.")
} else {
  OTHER_FILES += $$PWD/$${PROJECT_NAME}/$${PROJECT_NAME}.pri
}
