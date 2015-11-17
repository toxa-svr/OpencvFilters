#-------------------------------------------------
#
# Project created by QtCreator 2012-04-16T14:33:05
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = GraphEditor
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    GraphEditorWidget.cpp \
    GraphPort.cpp \
    GraphNode.cpp \
    GraphConnection.cpp

HEADERS  += \
    mainwindow.h \
    GraphEditorWidget.h \
    GraphNode.h \
    GraphPort.h \
    GraphConnection.h

FORMS += \
    mainwindow.ui

