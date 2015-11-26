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

