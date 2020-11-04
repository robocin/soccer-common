TEMPLATE = subdirs

# Version defines and project name.
include($$PWD/version.pri)

# The subdirectories contain folders that hold other '.pro' files.
SUBDIRS +=        \
  template        \
  include         \
  libs            \
  src             \
  test            \
  scripts

template.subdir   = $$PWD/template
include.subir     = $$PWD/include
libs.subdir       = $$PWD/libs
src.subdir        = $$PWD/src
test.subir        = $$PWD/test
scripts.subir     = $$PWD/scripts

src.depends = template libs
test.depends = template libs src

# For Qt Creator beautifier.
DISTFILES +=                  \
  $$PWD/.clang-format         \
  $$PWD/.clang-format-ignore
