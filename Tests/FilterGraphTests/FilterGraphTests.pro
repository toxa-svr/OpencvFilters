#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T10:07:56
#
#-------------------------------------------------

TEMPLATE    = app

QT          += testlib
QT          -= gui

CONFIG      += console testcase
CONFIG      -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"
INCLUDEPATH += ../../LibFilter



# -----------------------------------
# Output directories and names
# -----------------------------------
TARGET  = tst_FilterGraphTestsTest


# -----------------------------------
# Headers and sources
# -----------------------------------
SOURCES += \
    tst_FilterGraphTestsTest.cpp \
    ../../LibFilter/FilterGraph.cpp \
    ../../LibFilter/BaseFilter.cpp

HEADERS += \
    ../../LibFilter/FilterGraph.h \
    ../../LibFilter/BaseFilter.h

