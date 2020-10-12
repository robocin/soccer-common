!isEqual(QT_MAJOR_VERSION, 5): error(requires Qt Creator 5)
lessThan(QT_MINOR_VERSION, 15): error(requires Qt Creator at least 5.15)

DESTDIR     = bin                         # Target file directory (maybe replaced later).
OBJECTS_DIR = .qt-generated-files/objects # Intermediate object files directory.
MOC_DIR     = .qt-generated-files/moc     # Intermediate moc files directory.
UI_DIR      = .qt-generated-files/ui      # Intermediate ui files directory.

QT += core
QT += gui
QT += widgets
QT += opengl
QT += concurrent

CONFIG += c++17

include($$PWD/../version.pri)

# (OpenGL) Not sure if it works on Mac OS.
LIBS += -L OPENGL_gl_LIBRARY

# Linux specific libraries.
unix:!macx {
  LIBS += -lglut -lGLU # (OpenGL)
}

# Mac OS specifics libraries.
macx: {
  # To add.
}

win32: {
  error("this code isn't compatible with Windows OS.")
}
