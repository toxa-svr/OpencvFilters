#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T10:07:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_FilterGraphTestsTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_FilterGraphTestsTest.cpp \
            ../../FilterGraph/FilterGraph.cpp \
            ../../FilterGraph/BaseFilter.cpp

HEADERS += ../../FilterGraph/FilterGraph.h \
            ../../FilterGraph/BaseFilter.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../FilterGraph
