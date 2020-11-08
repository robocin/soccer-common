# ---------------------------------------------------------------------------- #
# Just paste this code in your 'include.pri'.                                  #
# WARNING: You may need to adjust the relative paths.                          #
# ---------------------------------------------------------------------------- #

PROJECT_NAME = $$fromfile($$PWD/../version.pri, PROJECT_NAME)

unix: LIBS += -L$$PWD/../lib -l$${PROJECT_NAME}

INCLUDEPATH += $$PWD

include($$PWD/$${PROJECT_NAME}/$${PROJECT_NAME}.pri)
