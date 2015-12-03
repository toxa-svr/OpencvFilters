#ifndef LIBFILTER_H
#define LIBFILTER_H

#include "FilterGraph.h"
#include "FilterAndWidget.h"
#include "FilterDescription.h"

// Class provides interface for all LibFilter library.
// Class is responsible for creation/deletion of filters, filter graph and filter widgets.

class LibFilter {
public:
    LibFilter();
    FilterDescription enumerateFilters() const;
    AbstractFilterWidget* createFilter(FilterId id);
    void save(/*TODO*/);
    void load(/*TODO*/);

private:
    FilterGraph filterGraph;
    QVector<FilterAndWidget> faws;
};

#endif // LIBFILTER_H
