#include <algorithm>
#include <cassert>
#include <QUuid>
#include "BaseFilter.h"

BaseFilter::BaseFilter(QObject* parent) : QObject(parent), alreadyProcessed(false) {}

bool BaseFilter::canProcessData() {
    bool dataIsAvailableInAllPorts = std::all_of(inPorts_.cbegin(), inPorts_.cend(), [](const FilterPort& port) {
       return !port.filterData().isNull();
    });

    return dataIsAvailableInAllPorts && !alreadyProcessed;
}

void BaseFilter::clear() {
    std::for_each(inPorts_.begin(), inPorts_.end(), [](FilterPort& port) {
        port.setFilterData(FilterData());
    });
    alreadyProcessed = false;
}

FilterPortDescriptionVector BaseFilter::inputs()  const {
    FilterPortDescriptionVector result;
    std::for_each(inPorts_.cbegin(), inPorts_.cend(), [&](const FilterPort& port) {
        result.push_back(port.description());
    });
    return result;
}
FilterPortDescriptionVector BaseFilter::outputs() const {
    FilterPortDescriptionVector result;
    std::for_each(outPorts_.cbegin(), outPorts_.cend(), [&](const FilterPort& port) {
        result.push_back(port.description());
    });
    return result;
}

void BaseFilter::processData() {
    assert(false);
}

QString BaseFilter::className() const {
    assert(false);
    return QString("Error: AbstractFilter");
}

FilterInstanceName BaseFilter::instanceName() {
    assert(false);
    return QString("Error: AbstractFilter_") + QUuid::createUuid().toString();
}
