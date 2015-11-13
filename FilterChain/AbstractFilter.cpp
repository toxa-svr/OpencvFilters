#include <algorithm>
#include <cassert>
#include <QUuid>
#include "AbstractFilter.h"

AbstractFilter::AbstractFilter(QObject* parent) : QObject(parent) {}

bool AbstractFilter::canProcessData() const {
    return std::all_of(inPorts_.cbegin(), inPorts_.cend(), [](const FilterPort& port) {
       return !port.filterData().isNull();
    });
}

void AbstractFilter::clear() {
    std::for_each(inPorts_.begin(), inPorts_.end(), [](FilterPort& port) {
        port.setFilterData(FilterData());
    });
}

FilterPortDescriptionVector AbstractFilter::inputs()  const {
    FilterPortDescriptionVector result;
    std::for_each(inPorts_.cbegin(), inPorts_.cend(), [&](const FilterPort& port) {
        result.push_back(port.description());
    });
    return result;
}
FilterPortDescriptionVector AbstractFilter::outputs() const {
    FilterPortDescriptionVector result;
    std::for_each(outPorts_.cbegin(), outPorts_.cend(), [&](const FilterPort& port) {
        result.push_back(port.description());
    });
    return result;
}

void AbstractFilter::processData() {
    assert(false);
}

QString AbstractFilter::className() const {
    assert(false);
    return QString("Error: AbstractFilter");
}

FilterObjectName AbstractFilter::objectName() {
    assert(false);
    return QString("Error: AbstractFilter_") + QUuid::createUuid().toString();
}
