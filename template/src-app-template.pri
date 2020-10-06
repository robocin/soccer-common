# -----------------------------------------------------------------------------#
# Just paste this code in your 'src.pro' and add 'main.cpp'.                   #
# WARNING: You may need to adjust the relative paths.                          #
# -----------------------------------------------------------------------------#

# Includes must contain the necessary relative includepaths.
include($$PWD/../template/template.pri)
include($$PWD/../libs/libs.pri)
include($$PWD/../src/src.pri)

# Putting the binary in the root of project.
DESTDIR = $$PWD/../bin # bin, because it's an app.

# The binary will have the same name as the project.
TARGET = $$PROJECT_NAME

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
