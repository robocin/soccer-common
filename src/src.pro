include($$PWD/../template/template.pri)
include($$PWD/../libs/libs.pri)
include($$PWD/../src/src.pri)

# Putting the binary in the root of project.
DESTDIR = $$PWD/../bin

# The binary will have the same name as the project.
TARGET = $$PROJECT_NAME

TEMPLATE = lib

# Default rules for deployment.
unix {
  target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
