TEMPLATE = subdirs

# Version defines and project name.
include($$PWD/version.pri)

# The subdirectories contain folders that hold other '.pro' files.
SUBDIRS +=       \
  $$PWD/template \
  $$PWD/include  \
  $$PWD/libs     \
  $$PWD/src      \
  $$PWD/test

# For Qt Creator beautifier.
DISTFILES += \
  $$PWD/uncrustify.cfg
