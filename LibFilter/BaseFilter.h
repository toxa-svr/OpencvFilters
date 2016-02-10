#pragma once

#include <QVector>
#include "FilterSettings.h"
#include "FilterPort.h"
#include "FilterId.h"

// Unique identifier for filter instances
typedef QString FilterInstanceName;

// Vector of filter ports
typedef QVector<FilterPort> FilterPortVector;

// Port index in a filter
typedef int PortIndex;

// Base class for filters
class BaseFilter : public QObject {
    Q_OBJECT

public:
    explicit BaseFilter(QObject* parent = nullptr);

    FilterSettings settings() const {return settings_;}

    virtual void processData();
    virtual QString className() const;
    virtual FilterInstanceName instanceName() const;

    FilterPortDescriptionVector inputs()  const;
    FilterPortDescriptionVector outputs() const;

    // Interface functions for FilterChain
    FilterPort* inPort (PortIndex i) {return &inPorts_ [i];}
    FilterPort* outPort(PortIndex i) {return &outPorts_[i];}
    void clear();
    bool canProcessData() const;

    FilterId filterId() const {return filterId_;}

signals:
    void infoToWidget(); // TODO какой здесь аргумент?

public slots:
    void setSettings(FilterSettings settings) {settings_ = settings;}

protected:
    void setInPorts(const FilterPortVector& ports) {inPorts_ = ports;}
    void setOutPorts(const FilterPortVector& ports) {outPorts_ = ports;}
    void setAlreadyProcessed() {alreadyProcessed = true;}
    void setFilterId(FilterId filterId);

private:
    FilterSettings settings_;
    FilterPortVector inPorts_;
    FilterPortVector outPorts_;
    bool alreadyProcessed;
    FilterId filterId_;
};

