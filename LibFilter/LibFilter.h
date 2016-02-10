#ifndef LIBFILTER_H
#define LIBFILTER_H

#include <vector>
#include <QJsonObject>
#include "FilterGraph.h"
#include "FilterAndWidget.h"
#include "FilterDescription.h"

// Class provides interface for all LibFilter library.
// Class is responsible for creation/deletion of filters, filter graph and filter widgets.

class LibFilter {
public:
    struct CreateFilterResult {
        AbstractFilterWidget* widget;
        FilterInstanceName instanceName;
    };

    LibFilter();
    LibFilter(const LibFilter&) = delete;
    LibFilter& operator=(const LibFilter&) = delete;
    ~LibFilter() = default;

    QVector<FilterDescription> enumerateFilters() const;

    CreateFilterResult createFilter(FilterId id);
    void removeFilter(FilterInstanceName instanceName);

    // Functions to modify data links between filters
    void addLink     (const FilterLink& filterLink);
    void removeLink  (const FilterLink& filterLink);
    QVector<FilterLink> links() const;

    // Functions to get image data
    void addDataToShow   (const FullPortAddress& from);
    void removeDataToShow(const FullPortAddress& from);
    FilterData dataToShow(const FullPortAddress& from) const;
    QVector<FullPortAddress> dataToShowInfo() const;

    void processFilters();

    QJsonObject save() const;
    void load(const QJsonObject& jsonObject);

private:
    std::unique_ptr<FilterGraph> filterGraph;
    std::vector<FilterAndWidget> faws;
};

#endif // LIBFILTER_H
