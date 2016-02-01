#-------------------------------------------------
#
# Project created by QtCreator 2012-04-16T14:33:05
#
#-------------------------------------------------


TEMPLATE = app

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# -----------------------------------
# Output directories and names
# -----------------------------------
TARGET = GraphEditor



# -----------------------------------
# Headers and sources
# -----------------------------------
SOURCES += main.cpp\
    mainwindow.cpp \
    #GraphEditorWidget.cpp \
    #GraphPort.cpp \
    #GraphNode.cpp \
    #GraphConnection.cpp
    testwidget_1.cpp \
    testwidget_2.cpp

HEADERS  += \
    mainwindow.h \
    #GraphEditorWidget.h \
    #GraphNode.h \
    #GraphPort.h \
    #GraphConnection.h
    testwidget_1.h \
    testwidget_2.h

FORMS += \
    mainwindow.ui \
    testwidget_1.ui \
    testwidget_2.ui



# -----------------------------------
# Libraries
# -----------------------------------
INCLUDEPATH += $$PWD/../NodeEditorWidget/inc
LIBS += -L$$PWD/../NodeEditorWidget/bin

Debug:  LIBS += NodeEditorWidgetd.lib
Release:LIBS += NodeEditorWidget.lib

