TEMPLATE = subdirs

ROBOCIN_APP = src
ROBOCIN_LIB = include

# Project type. Choose one of the two options above.
PROJECT_TYPE =

isEmpty(PROJECT_TYPE): error(PROJECT_TYPE is not defined.)

# Version defines and project name.
include($$PWD/version.pri)

# The subdirectories contain folders that hold other '.pro' files.
SUBDIRS +=         \
  template         \
  $${PROJECT_TYPE} \
  libs             \
  test             \
  scripts

template.subdir          = $$PWD/template
$${PROJECT_TYPE}.subir   = $$PWD/$${PROJECT_TYPE}
libs.subdir              = $$PWD/libs
test.subir               = $$PWD/test
scripts.subir            = $$PWD/scripts

$${PROJECT_TYPE}.depends = template libs
test.depends = template libs $${PROJECT_TYPE}

# For Qt Creator beautifier.
DISTFILES +=                  \
  $$PWD/.clang-format         \
  $$PWD/.clang-format-ignore
