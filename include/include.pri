LIB_NAME = $$fromfile($$PWD/../version.pri, PROJECT_NAME)

unix: LIBS += -L$$PWD/../lib -l$${LIB_NAME}

INCLUDEPATH += $$PWD

include($$PWD/../libs/libs.pri)
include($$PWD/$${LIB_NAME}/$${LIB_NAME}.pri)
