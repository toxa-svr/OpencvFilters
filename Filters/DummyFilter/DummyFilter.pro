#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T13:00:52
#
#-------------------------------------------------
# ATTENTION: Path to OpenCV must be added to the OPENCV_DIR variable.

TEMPLATE        = lib

CONFIG         += plugin

QT             += widgets


# -----------------------------------
# This macro will br used to generate .cpp and .h filenames:
# Example: for filtername "My" will be generated
#   MyFilterPlugin.h
#   MyFilterPlugin.cpp
#   MyFilter.h
#   MyFilter.cpp
#   MyWidget.h
#   MyWidget.cpp
#   MyWidget.ui
# and result library name MyFilter or MyFilterd
# -----------------------------------
FILTERNAME = Dummy


# -----------------------------------
# Output directories and names
# -----------------------------------
# Set library name using "d" for debug configuration.
Debug:  TARGET = $${FILTERNAME}Filterd
Release:TARGET = $${FILTERNAME}Filter

# And specify where to put the target file
DESTDIR = $$PWD/../../bin


# Some magic for unix
# Copy output file to target directory,
# but to actually make the file copy, you will have to execute make install
unix {
    Debug:  target.file = $${FILTERNAME}Filterd
    Release:target.file = $${FILTERNAME}Filter

    target.path = /usr/lib
    INSTALLS += target
}



# -----------------------------------
# Headers and sources
# -----------------------------------
# Add, .h .cpp and .ui files using FILTERNAME macro to generate filenames
HEADERS += \
    $${FILTERNAME}Filter.h \
    $${FILTERNAME}Widget.h \
    $${FILTERNAME}FilterPlugin.h

SOURCES += \
    $${FILTERNAME}Filter.cpp \
    $${FILTERNAME}Widget.cpp \
    $${FILTERNAME}FilterPlugin.cpp

FORMS += \
    $${FILTERNAME}Widget.ui



# -----------------------------------
# Libraries
# -----------------------------------
#TODO to be removed
LIBFILTER_DIR = $$PWD/../../LibFilter
message($$(OPENCV_DIR))
message($${LIBFILTER_DIR})


INCLUDEPATH += $$(OPENCV_DIR)/build/include
INCLUDEPATH += $$LIBFILTER_DIR

LIBS += -L$$(OPENCV_DIR)/build/x64/vc12/lib
#LIBS += -L$$(OPENCV_DIR)/build/x86/vc12/lib
LIBS += -L$${LIBFILTER_DIR}/bin

Debug:  LIBS += opencv_ts300d.lib \
                opencv_world300d.lib \
                LibFilterd.lib
Release:LIBS += opencv_ts300.lib \
                opencv_world300.lib \
                LibFilter.lib

