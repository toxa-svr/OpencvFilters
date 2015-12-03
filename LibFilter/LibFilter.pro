#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T18:12:03
#
#-------------------------------------------------
# ATTENTION: Path to OpenCV must be added to the OPENCV_DIR variable.


TEMPLATE = lib

CONFIG += staticlib


# -----------------------------------
# Output directories and names
# -----------------------------------
# For windows
# Set library name using "d" for debug configuration.
CONFIG (debug, debug|release) {
    TARGET = FilterGraphd
} else {
    TARGET = FilterGraph
}
# And specify where to put the target file
DESTDIR = ../bin_debug

# Some magic for unix
# Copy output file to target directory,
# but to actually make the file copy, you will have to execute make install
unix {
    CONFIG (debug, debug|release) {
        target.file = FilterGraphd
    } else {
        target.file = FilterGraph
    }
    target.path = /usr/lib
    INSTALLS += target
}



# -----------------------------------
# Headers and sources
# -----------------------------------
SOURCES += \
    FilterFactory.cpp \
    FilterPort.cpp \
    BaseFilter.cpp \
    FilterGraph.cpp \
    LibFilter.cpp \
    FilterAndWidget.cpp

HEADERS += \
    FilterInterface.h \
    FilterSettings.h \
    FilterFactory.h \
    FilterPort.h \
    FilterData.h \
    FilterPluginInterface.h \
    BaseFilter.h \
    FilterGraph.h \
    FilterId.h \
    LibFilter.h \
    FilterAndWidget.h \
    FilterDescription.h \
    AbstractFilterWidget.h



# -----------------------------------
# Libraries
# -----------------------------------

INCLUDEPATH += $$(OPENCV_DIR)/build/include
LIBS += -L$$(OPENCV_DIR)/build/x64/vc12/lib
#LIBS += -L$$(OPENCV_DIR)/build/x86/vc12/lib

CONFIG(debug, debug|release) {
    LIBS += opencv_ts300d.lib \
        opencv_world300d.lib
} else {
    LIBS += opencv_ts300.lib \
        opencv_world300.lib
}


