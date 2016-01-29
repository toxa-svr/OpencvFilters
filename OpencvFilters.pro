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


