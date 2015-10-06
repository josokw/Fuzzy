TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../FuzzyEngine
DEPENDPATH += ../../FuzzyEngine

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    RCcircuit.h \
    AppInfo.h
