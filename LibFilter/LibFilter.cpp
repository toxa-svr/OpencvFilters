#include "FilterFactory.h"
#include "LibFilter.h"

LibFilter::LibFilter() {

}

LibFilter::~LibFilter() {

}

QVector<FilterDescription> LibFilter::enumerateFilters() const {
    return FilterFactory::enumerateFilters();
}

AbstractFilterWidget* LibFilter::createFilter(FilterId id) {
    faws.push_back(FilterFactory::createFilter(id));
    filterGraph.addFilter(faws.last().filter());
    return faws.last().filterWidget();
}

void LibFilter::removeFilter(FilterInstanceName instanceName) {
    filterGraph.removeFilter(instanceName);
    auto pend = std::remove_if(faws.begin(), faws.end(), [&](FilterAndWidget& faw) {
        return faw.filter()->instanceName() == instanceName;
    });
    faws.erase(pend, faws.end());
}

// Functions to modify data links between filters
void LibFilter::addLink     (const FilterLink& filterLink) {
    filterGraph.addLink(filterLink);
}

void LibFilter::removeLink  (const FilterLink& filterLink) {
    filterGraph.removeLink(filterLink);
}

QVector<FilterLink> LibFilter::links() const {
    return filterGraph.links();
}

// Functions to get image data
void LibFilter::addDataToShow   (const FullPortAddress& from) {
    filterGraph.addDataToShow(from);
}

void LibFilter::removeDataToShow(const FullPortAddress& from) {
    filterGraph.removeDataToShow(from);
}

FilterData LibFilter::dataToShow(const FullPortAddress& from) const {
    return filterGraph.dataToShow(from);
}

QVector<FullPortAddress> LibFilter::dataToShowInfo() const {
    return filterGraph.dataToShowInfo();
}

void LibFilter::processFilters() {
    filterGraph.processFilters();
}
