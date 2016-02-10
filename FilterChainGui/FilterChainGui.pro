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
    mainwindow.cpp \
    NodeItemProxy.cpp \
    testwidget_1.cpp \
    testwidget_2.cpp

HEADERS += \
    mainwindow.h \
    NodeItemProxy.h \
    testwidget_1.h \
    testwidget_2.h

FORMS += \
    testwidget_1.ui \
    testwidget_2.ui



# -----------------------------------
# Libraries
# -----------------------------------
INCLUDEPATH += $$PWD/../NodeEditorWidget/inc \
LIBS += -L$$PWD/../NodeEditorWidget/bin

INCLUDEPATH += $$PWD/../LibFilter/
LIBS += -L$$PWD/../LibFilter/bin


Debug:  LIBS += NodeEditorWidgetd.lib \
                LibFilterd.lib
Release:LIBS += NodeEditorWidget.lib \
                LibFilter.lib


