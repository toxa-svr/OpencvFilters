#include "DummyFilter.h"

size_t DummyFilter::instanceCounter = 0;

DummyFilter::DummyFilter(QObject* parent) : BaseFilter(parent) {
    instanceName_ = className() + " " + QString::number(instanceCounter);

    ++instanceCounter;
    if (instanceCounter == 0)
        throw std::runtime_error("Maximum amount of DummyFilter objects is exceeded");

    // TODO порты вывода
    FilterPortDescription description = {"Dummy port", "any"};
    setOutPorts({FilterPort(description)});
    setInPorts({FilterPort(description)});
}

DummyFilter::~DummyFilter() = default;

void DummyFilter::processData() {
    outPort(0)->setFilterData(inPort(0)->filterData());
    setAlreadyProcessed();
}

FilterInstanceName DummyFilter::instanceName() const {
    return instanceName_;
}







