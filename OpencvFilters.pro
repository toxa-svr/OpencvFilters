TEMPLATE = subdirs

#TODO these variables should be used
#LIBFILTER_DIR = $$PWD/LibFilter
#NODEEDITORWIDGET_DIR = $$PWD/NodeEditorWidget

SUBDIRS += \
    LibFilter \
    FilterChainGui \
    Filters \
    Tests \
    NodeEditorWidget \
    ExpanderWidget

FilterChainGui.depends      = LibFilter NodeEditorWidget
Filters.depends             = LibFilter ExpanderWidget
Tests.depends               = LibFilter FilterChainGui Filters
NodeEditorWidget            = ExpanderWidget

