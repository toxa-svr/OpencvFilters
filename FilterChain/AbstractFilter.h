#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include <QObject>
#include <QVector>
#include "FilterSettings.h"
#include "FilterPort.h"

// Идентификатор объекта фильтра
typedef QString FilterObjectName;

// Вектор описания портов фильтра
typedef QVector<FilterPortDescription> FilterPortDescriptionVector;

// Вектор портов фильтра
typedef QVector<FilterPort> FilterPortVector;

// Индекс порта внутри фильтра
typedef int PortIndex;

// Абстрактный класс фильтра
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

    // Функции, представляющие интерфейс для FilterChain
    FilterPort* inPort (PortIndex i) {return &inPorts_ [i];}
    FilterPort* outPort(PortIndex i) {return &outPorts_[i];}
    bool canProcessData() const;

signals:
    void infoToWidget(); // TODO

public slots:
    void setSettings(FilterSettings settings) {settings_ = settings;}

protected:
    FilterSettings settings_;
    FilterPortVector inPorts_;
    FilterPortVector outPorts_;
};


// Declare interface for all plugins
#define AbstractFilter_iid "org.OpencvFilters.AbstractFilter"
Q_DECLARE_INTERFACE(AbstractFilter, AbstractFilter_iid)



#endif // ABSTRACTFILTER_H
