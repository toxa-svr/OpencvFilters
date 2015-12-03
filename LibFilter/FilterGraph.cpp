#include <cassert>

//#define _SCL_SECURE_NO_WARNINGS // disable warning about std::transform call

//#include <QCoreApplication>
#include "FilterGraph.h"

//----------------------------------------------------------------------------------------------------------------------
// FilterLink and FullPortAddress operators
//----------------------------------------------------------------------------------------------------------------------
bool operator==(const FilterLink& lhs, const FilterLink& rhs) {
    return lhs.from == rhs.from && lhs.to == rhs.to;
}
bool operator!=(const FilterLink& lhs, const FilterLink& rhs) {
    return !(lhs == rhs);
}

bool operator==(const FullPortAddress& lhs, const FullPortAddress& rhs) {
    return lhs.filter == rhs.filter && lhs.port == rhs.port;
}

bool operator!=(const FullPortAddress& lhs, const FullPortAddress& rhs) {
    return !(lhs == rhs);
}

bool operator< (const FullPortAddress& lhs, const FullPortAddress& rhs) {
    return lhs.filter < rhs.filter || lhs.port < rhs.port;
}

bool operator> (const FullPortAddress& lhs, const FullPortAddress& rhs) {
    return rhs < lhs;
}

//----------------------------------------------------------------------------------------------------------------------
// FilterGraph class members
//----------------------------------------------------------------------------------------------------------------------
FilterGraph::FilterGraph(QObject* parent) : QObject(parent) {}

FilterGraph::~FilterGraph() {}

void FilterGraph::addFilter(BaseFilter* filter) {
    assert(filter);
    filters_.push_back(filter);
}

void FilterGraph::removeFilter(FilterInstanceName instanceName) {
    filters_.remove(findFilterIndex(instanceName));
}

QVector<FilterInstanceName> FilterGraph::filters() const {
    QVector<FilterInstanceName> result(filters_.size());
    std::transform(filters_.cbegin(), filters_.cend(), result.begin(), [](const BaseFilter* filter) {
        return filter->instanceName();
    });
    return result;
}

void FilterGraph::addLink(const FilterLink& filterLink) {
    links_.push_back(filterLink);
}

void FilterGraph::removeLink(const FilterLink& filterLink) {
    links_.erase(std::find_if(links_.begin(), links_.end(), [&](const FilterLink& link) {
        return filterLink == link;
    }));
}

QVector<FilterLink> FilterGraph::links() const {
    return links_;
}

void FilterGraph::addDataToShow(const FullPortAddress& from) {
    dataToShowAddressVector.push_back(from);
}

void FilterGraph::removeDataToShow(const FullPortAddress& from) {
    dataToShowAddressVector.erase(std::find(dataToShowAddressVector.begin(), dataToShowAddressVector.end(), from));
}

FilterData FilterGraph::dataToShow(const FullPortAddress& from) const {
    return dataToShowMap[from];
}

QVector<FullPortAddress> FilterGraph::dataToShowInfo() const {
    return dataToShowAddressVector;
}

void FilterGraph::processFilters() { // TODO говнокод
    std::for_each(filters_.begin(), filters_.end(), [](BaseFilter* filter) {
        filter->clear();
    });

    QVector<BaseFilter*> processedFilters;

    while(true) {
        auto filter = std::find_if(filters_.begin(), filters_.end(), [&](BaseFilter* filter) {
            return filter->canProcessData();
        });

        if (filter == filters_.end())
            break;
        if (std::find(processedFilters.cbegin(), processedFilters.cend(), *filter) != processedFilters.cend()) {
            assert(false);
            throw std::runtime_error("cycle in the filter graph is found");
        } else
            processedFilters.push_back(*filter);

        (*filter)->processData();


        std::for_each(dataToShowAddressVector.cbegin(), dataToShowAddressVector.cend(), [&] (const FullPortAddress& address) {
           if (address.filter == (*filter)->instanceName())
               dataToShowMap[address] = (*filter)->outPort(address.port)->filterData();
        });

        std::for_each(links_.cbegin(), links_.cend(), [&](const FilterLink& link) {
            if (link.from.filter == (*filter)->instanceName()) {
                auto data = (*filter)->outPort(link.from.port)->filterData();
                filters_[findFilterIndex(link.to.filter)]->inPort(link.to.port)->setFilterData(data);
            }
        });
    }
}

int FilterGraph::findFilterIndex(FilterInstanceName instanceName) {
    for (int i = 0; i < filters_.size(); ++i)
        if (filters_[i]->instanceName() == instanceName)
            return i;

    assert(false);
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------
// Non member operators for FilterGraph
//----------------------------------------------------------------------------------------------------------------------

struct FilterInfo {
    FilterId filterId;
    FilterInstanceName instanceName;
    FilterSettings settings;
};

//QDataStream &operator<<(QDataStream& stream, const FilterGraph& filterGraph) {
//    filterGraph.filters();// TODO доделать
//    QVector<FilterInfo> filterInfo;

//    stream << filterInfo;
//    stream << filterGraph.links();
//    stream << filterGraph.dataToShowInfo();
//    return stream;
//}

//QDataStream &operator>>(QDataStream& stream, FilterGraph& filterGraph) {
//    return stream;
//}
