# ---------------------------------------------------------------------------- #
# Just paste this code in your 'src.pro'.                                      #
# WARNING: You may need to adjust the relative paths.                          #
# ---------------------------------------------------------------------------- #

# Includes must contain the necessary relative includepaths.
include($$PWD/../template/template.pri)
include($$PWD/../libs/libs.pri)
include($$PWD/../src/src.pri)

# Putting the binary in the root of project.
DESTDIR = $$PWD/../lib # lib, because it's a library.

# The binary will have the same name as the project.
TARGET = $$PROJECT_NAME

TEMPLATE = lib

# Default rules for deployment.
unix {
  target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
