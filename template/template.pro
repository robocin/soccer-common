TEMPLATE = subdirs

include($$PWD/template.pri)

DISTFILES +=           \
  $$PWD/src-app-template.pri \
  $$PWD/src-lib-template.pri \
  $$PWD/test-template.h      \
  $$PWD/test-template.pri    \
  $$PWD/main.cpp
