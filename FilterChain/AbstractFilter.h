#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include <QObject>
#include <QVector>
#include "FilterSettings.h"
#include "FilterPort.h"

class FilterObjectName {};
typedef QVector<FilterPortDescription> FilterPortDescriptionVector;
typedef QVector<FilterPort> FilterPortVector;

typedef int PortIndex;

class AbstractFilter : public QObject {
    Q_OBJECT

public:
    explicit AbstractFilter(QObject* parent = nullptr);
    FilterSettings settings() const {return settings_;}
    virtual void processData() = 0;
    virtual FilterPortDescriptionVector inputs()  const;
    virtual FilterPortDescriptionVector outputs() const;
    virtual QString className() const = 0;
    virtual FilterObjectName objectName() const = 0;

signals:
    void infoToWidget(); // TODO

public slots:
    void setSettings(FilterSettings settings) {settings_ = settings;}

protected:
    FilterSettings settings_;
    FilterPortVector inPorts;
    FilterPortVector outPorts;

};


// Decalare interface for all plugins
#define AbstractFilter_iid "org.OpencvFilters.AbstractFilter"
Q_DECLARE_INTERFACE(AbstractFilter, AbstractFilter_iid)



#endif // ABSTRACTFILTER_H
