TEMPLATE = lib
CONFIG += staticlib

DESTDIR = $$PWD/bin

TARGET   = $$qtLibraryTarget($$TARGET)

QT      += widgets

CONFIG += c++11

HEADERS += \
    expanderwidget.h 

SOURCES += \
    expanderwidget.cpp 

RESOURCES += \
    res.qrc


