#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T18:03:42
#
#-------------------------------------------------

TEMPLATE    = app

QT          += core gui widgets


# -----------------------------------
# Output directories and names
# -----------------------------------
TARGET = FilterChainGui


# -----------------------------------
# Headers and sources
# -----------------------------------
SOURCES += \
    main.cpp\
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui



# -----------------------------------
# Libraries
# -----------------------------------
INCLUDEPATH += $$PWD/../NodeEditorWidget/inc
LIBS += -L$$PWD/../NodeEditorWidget/bin

Debug:  LIBS += NodeEditorWidgetd.lib
Release:LIBS += NodeEditorWidget.lib


