unix: LIBS += -L$$OUT_PWD/../../bin -lsoccer-common

INCLUDEPATH += $$PWD/..

include($$PWD/../../src/src.pri)

HEADERS += $$PWD/soccer-common
