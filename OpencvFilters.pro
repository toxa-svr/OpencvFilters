TEMPLATE = subdirs

#TODO these variables should be used
#LIBFILTER_DIR = $$PWD/LibFilter
#NODEEDITORWIDGET_DIR = $$PWD/NodeEditorWidget

SUBDIRS += \
    LibFilter \
    FilterChainGui \
    Filters \
    Tests \
    NodeEditorWidget


FilterChainGui.depends = LibFilter
Filters.depends        = LibFilter
Tests.depends          = LibFilter FilterChainGui Filters


