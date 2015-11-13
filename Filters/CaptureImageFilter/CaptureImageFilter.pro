#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T13:00:52
#
#-------------------------------------------------


# This macro will br used to generate .cpp and .h filenames:
# Example: for filtername "My" will be generated
#   MyFilter.h
#   MyFilter.cpp
#   MyWidget.h
#   MyWidget.cpp
#   MyWidget.ui
# and result library name MyFilter or MyFilterd
# -----------------------------------

FILTERNAME = CaptureImage

# -----------------------------------



TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets


# For windows
# Set library name using "d" for debug configuration.
CONFIG (debug, debug|release) {
    TARGET = $${FILTERNAME}Filterd
} else {
    TARGET = $${FILTERNAME}Filter
}
# And specify where to put the target dll file
DESTDIR = ../bin_debug


# Some magic for unix
# Copy output file to target directory,
# but to actually make the file copy, you will have to execute make install
unix {
    CONFIG (debug, debug|release) {
        target.file = $${FILTERNAME}filterd
    } else {
        target.file = $${FILTERNAME}filter
    }
    target.path = /usr/lib
    INSTALLS += target
}


# Add, .h .cpp and .ui files using FILTERNAME macro to generate filenames
INCLUDEPATH    += ../../FilterGraph
HEADERS        += $${FILTERNAME}Filter.h   \
                  $${FILTERNAME}Widget.h \
    CaptureImageFilterPlugin.h
SOURCES        += $${FILTERNAME}Filter.cpp \
                  $${FILTERNAME}Widget.cpp \
    CaptureImageFilterPlugin.cpp

FORMS          += $${FILTERNAME}Widget.ui


# Path to OpenCV must be added to the OPENCV_DIR variable.
# Path to Boost  must be added to the BOOST_DIR variable.
INCLUDEPATH += $$(OPENCV_DIR)/build/include \
               $$(BOOST_DIR)

LIBS += -L$$(OPENCV_DIR)/build/x64/vc12/lib

CONFIG(debug, debug|release) {
    LIBS += opencv_ts300d.lib \
        opencv_world300d.lib \
        ../../bin_debug/FilterGraphd.lib
} else {
    LIBS += opencv_ts300.lib \
        opencv_world300.lib \
        ../../bin_release/FilterGraph.lib
}
