#pragma once

#include <QVector>
#include <QMap>
#include "BaseFilter.h"

// Full qualified filter port address
struct FullPortAddress {
    FilterInstanceName filter;
    PortIndex port;
};

// Structure describes a link between filters
struct FilterLink {
    FullPortAddress from;
    FullPortAddress to;
};

bool operator==(const FilterLink& lhs, const FilterLink& rhs);
bool operator!=(const FilterLink& lhs, const FilterLink& rhs);

bool operator==(const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator!=(const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator< (const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator> (const FullPortAddress& lhs, const FullPortAddress& rhs);


// Graph of connected filters
class FilterGraph : public QObject {
    Q_OBJECT

public:
    explicit FilterGraph(QObject* parent = nullptr);
    FilterGraph(const FilterGraph&) = delete;
    FilterGraph& operator=(const FilterGraph&) = delete;
    ~FilterGraph();

    // Functions for the filter graph modification
    void addFilter   (BaseFilter* filter);
    void removeFilter(FilterInstanceName objectInstance);
    void addLink     (const FilterLink& filterLink);
    void removeLink  (const FilterLink& filterLink);

    // Functions to get image data
    void addDataToShow   (const FullPortAddress& from);
    void removeDataToShow(const FullPortAddress& from);
    FilterData dataToShow(const FullPortAddress& from) const;

    void processFilters();

private:
    int findFilterIndex(FilterInstanceName objectInstance);

    QVector<BaseFilter*> filters;
    QVector<FilterLink> links;
    QVector<FullPortAddress> dataToShowAddressVector;
    QMap<FullPortAddress, FilterData> dataToShowMap;
};
