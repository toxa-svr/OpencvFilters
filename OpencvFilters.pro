TEMPLATE = subdirs


SUBDIRS += \
    FilterGraph \
    FilterChainGui \
    Filters \
    Tests \
    GraphEditorWidget


FilterChainGui.depends = FilterGraph
Filters.depends = FilterGraph
Tests.depends = FilterGraph FilterChainGui Filters
