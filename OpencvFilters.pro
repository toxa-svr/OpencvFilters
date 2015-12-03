TEMPLATE = subdirs


SUBDIRS += \
    LibFilter \
    FilterChainGui \
    Filters \
    Tests \
    GraphEditorWidget

    Tests

FilterChainGui.depends = LibFilter
Filters.depends        = LibFilter
Tests.depends          = LibFilter FilterChainGui Filters
