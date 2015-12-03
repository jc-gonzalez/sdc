include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += . ../src
LIBS += -L../src -lsdc -L../json -ljson
