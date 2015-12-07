#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T13:10:15
#
#-------------------------------------------------

QT       += testlib widgets

TARGET = tst_LibFilterTest
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../LibFilter

HEADERS +=  ../../LibFilter/FilterGraph.h \
    ../../LibFilter/BaseFilter.h


SOURCES += tst_LibFilterTest.cpp \
    ../../LibFilter/FilterGraph.cpp \
    ../../LibFilter/BaseFilter.cpp \
    ../../LibFilter/FilterAndWidget.cpp \
    ../../LibFilter/FilterFactory.cpp \
    ../../LibFilter/LibFilter.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
