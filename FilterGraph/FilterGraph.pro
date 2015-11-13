#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T18:12:03
#
#-------------------------------------------------


# Path to OpenCV must be added to the OPENCV_DIR variable.
# Path to Boost  must be added to the BOOST_DIR variable.

# For windows
# Set library name using "d" for debug configuration.
CONFIG (debug, debug|release) {
    TARGET = $${FILTERNAME}FilterGraphd
} else {
    TARGET = $${FILTERNAME}FilterGraph
}
# And specify where to put the target dll file
DESTDIR = ../bin_debug

TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    FilterFactory.cpp \
    FilterPort.cpp \
    BaseFilter.cpp \
    FilterGraph.cpp

HEADERS += \
    FilterInterface.h \
    FilterSettings.h \
    FilterFactory.h \
    FilterPort.h \
    FilterData.h \
    FilterPluginInterface.h \
    BaseFilter.h \
    FilterGraph.h

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
