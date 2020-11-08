TEMPLATE = subdirs

# Version defines and project name.
include($$PWD/version.pri)

# The subdirectories contain folders that hold other '.pro' files.
SUBDIRS +=        \
  template        \
  include         \
  libs            \
  test            \
  scripts

template.subdir   = $$PWD/template
include.subir     = $$PWD/include
libs.subdir       = $$PWD/libs
test.subir        = $$PWD/test
scripts.subir     = $$PWD/scripts

include.depends = template libs
test.depends = template libs include

# For Qt Creator beautifier.
DISTFILES +=                  \
  $$PWD/.clang-format         \
  $$PWD/.clang-format-ignore
