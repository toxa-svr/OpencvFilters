#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T10:07:56
#
#-------------------------------------------------

TEMPLATE    = app

QT          += testlib
QT          -= gui

CONFIG      += console
CONFIG      -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD/\\\"
INCLUDEPATH += ../../FilterGraph



# -----------------------------------
# Output directories and names
# -----------------------------------
TARGET  = tst_FilterGraphTestsTest


# -----------------------------------
# Headers and sources
# -----------------------------------
SOURCES += \
    tst_FilterGraphTestsTest.cpp \
    ../../FilterGraph/FilterGraph.cpp \
    ../../FilterGraph/BaseFilter.cpp

HEADERS += \
    ../../FilterGraph/FilterGraph.h \
    ../../FilterGraph/BaseFilter.h

