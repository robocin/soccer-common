TEMPLATE = subdirs

include($$PWD/template.pri)

DISTFILES +=                         \
  $$PWD/app-src-pro-template.pri     \
  $$PWD/app-src-pri-template.pri     \
  $$PWD/lib-include-pro-template.pri \
  $$PWD/lib-include-pri-template.pri \
$$PWD/test-template.h              \
  $$PWD/test-template.pri            \
  $$PWD/subdir-project-template.pri  \
  $$PWD/main.cpp
