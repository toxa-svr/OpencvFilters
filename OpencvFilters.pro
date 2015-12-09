TEMPLATE = subdirs


SUBDIRS += \
    LibFilter \
    FilterChainGui \
    Filters \
    Tests \
    NodeEditorWidget \
    GraphEditorWidget


FilterChainGui.depends = LibFilter
Filters.depends        = LibFilter
Tests.depends          = LibFilter FilterChainGui Filters


#TODO these variables should be used
#LIBFILTER_DIR = $$PWD/LibFilter
#NODEEDITORWIDGET_DIR = $$PWD/NodeEditorWidget
