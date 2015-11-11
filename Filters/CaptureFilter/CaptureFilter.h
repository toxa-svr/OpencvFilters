#ifndef CAPTUREFILTER_H
#define CAPTUREFILTER_H

#include "AbstractFilter.h"


class CaptureFilter : public AbstractFilter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.OpencvFilters.FilterInterface" FILE "CaptureFilter.json")
    Q_INTERFACES(AbstractFilter)

public:
    CaptureFilter(QObject* parent = nullptr);
    ~CaptureFilter();

    void processData();
    QString className() const {return "CaptureFilter";}
    FilterObjectName objectName() const {return FilterObjectName();}
};

#endif // CAPTUREFILTER_H
