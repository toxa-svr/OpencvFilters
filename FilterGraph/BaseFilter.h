#pragma once

#include <QVector>
#include "FilterSettings.h"
#include "FilterPort.h"

// Unique identifier for filter instances
typedef QString FilterInstanceName;

// Vector of filter port descriptions
typedef QVector<FilterPortDescription> FilterPortDescriptionVector;

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
    virtual FilterInstanceName instanceName();

    FilterPortDescriptionVector inputs()  const;
    FilterPortDescriptionVector outputs() const;

    // Interface functions for FilterChain
    FilterPort* inPort (PortIndex i) {return &inPorts_ [i];}
    FilterPort* outPort(PortIndex i) {return &outPorts_[i];}
    void clear();
    bool canProcessData();

signals:
    void infoToWidget(); // TODO

public slots:
    void setSettings(FilterSettings settings) {settings_ = settings;}

protected:
    void setInPorts(const FilterPortVector& ports) {inPorts_ = ports;}
    void setOutPorts(const FilterPortVector& ports) {outPorts_ = ports;}
    void setAlreadyProcessed() {alreadyProcessed = true;}

private:
    FilterSettings settings_;
    FilterPortVector inPorts_;
    FilterPortVector outPorts_;
    bool alreadyProcessed;
};

