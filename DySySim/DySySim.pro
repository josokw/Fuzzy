#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T07:16:45
#
#-------------------------------------------------

QT -= core gui

TARGET = DySySim
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

CONFIG(debug, debug|release) {
    TARGET = DySySimDebug
}
CONFIG(release, debug|release) {
    TARGET = DySySim
    DEFINES += NDEBUG
}

SOURCES += \
    DySySim.cpp \
    SimBlock.cpp \
    Connecting.cpp
HEADERS += \
    DySySim.h \
    SimBlock.h \
    LibInfoDySySim.h \
    Connecting.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
