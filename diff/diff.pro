TEMPLATE = app
TARGET = diff
INCLUDEPATH += .

QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

SOURCES += \
        main.cpp \
        window.cpp \
    sequence.cpp

HEADERS += \
        window.h \
    sequence.h
