#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

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

    virtual void processData();
    virtual QString className() const;
    virtual FilterObjectName objectName();

    FilterPortDescriptionVector inputs()  const;
    FilterPortDescriptionVector outputs() const;

    // Функции, представляющие интерфейс для FilterChain
    FilterPort* inPort (PortIndex i) {return &inPorts_ [i];}
    FilterPort* outPort(PortIndex i) {return &outPorts_[i];}
    void clear();
    bool canProcessData() const;

signals:
    void infoToWidget(); // TODO

public slots:
    void setSettings(FilterSettings settings) {settings_ = settings;}

protected:
    void setInPorts(const FilterPortVector& ports) {inPorts_ = ports;}
    void setOutPorts(const FilterPortVector& ports) {outPorts_ = ports;}

private:
    FilterSettings settings_;
    FilterPortVector inPorts_;
    FilterPortVector outPorts_;
};


// Declare interface for all plugins
#define AbstractFilter_iid "org.OpencvFilters.AbstractFilter"
Q_DECLARE_INTERFACE(AbstractFilter, AbstractFilter_iid)

class MyTestFilter : public AbstractFilter {
    Q_OBJECT
public:
    MyTestFilter(QObject* parent) : AbstractFilter(parent) {}
};

#endif // ABSTRACTFILTER_H
