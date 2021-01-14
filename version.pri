PROJECT_NAME = soccer-common

isEmpty(PROJECT_NAME): error(PROJECT_NAME is not defined.)

PROJECT_PATH = $$PWD

VER_MAJOR = 1
VER_MINOR = 4
VER_PATCH = 1

PROJECT_VERSION = $${VER_MAJOR}.$${VER_MINOR}.$${VER_PATCH}

DEFINES += ROBOCIN_PROJECT_NAME=\\\"$${PROJECT_NAME}\\\"
DEFINES += ROBOCIN_PROJECT_PATH=\\\"$${PROJECT_PATH}\\\"

DEFINES += ROBOCIN_PROJECT_VERSION_MAJOR=$${VER_MAJOR}
DEFINES += ROBOCIN_PROJECT_VERSION_MINOR=$${VER_MINOR}
DEFINES += ROBOCIN_PROJECT_VERSION_PATCH=$${VER_PATCH}

DEFINES += ROBOCIN_PROJECT_VERSION=\\\"v$${PROJECT_VERSION}\\\"
