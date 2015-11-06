#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T18:12:03
#
#-------------------------------------------------


# Path to OpenCV must be added to the OPENCV_DIR variable.
# Path to Boost  must be added to the BOOST_DIR variable.


QT       -= gui


TARGET = FilterChain
TEMPLATE = lib
CONFIG += staticlib

SOURCES += filterchain.cpp

HEADERS += filterchain.h \
            filterinterface.h

INCLUDEPATH += $$(OPENCV_DIR)/build/include \
               $$(BOOST_DIR)

LIBS += -L$$(OPENCV_DIR)/build/x64/vc12/lib


CONFIG(debug, debug|release) {
    LIBS += opencv_ts300d.lib \
        opencv_world300d.lib
} else {
    LIBS += opencv_ts300.lib \
        opencv_world300.lib
}


unix {
    target.path = /usr/lib
    INSTALLS += target
}
