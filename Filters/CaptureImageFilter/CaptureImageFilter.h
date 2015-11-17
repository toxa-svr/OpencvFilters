#pragma once

#include "BaseFilter.h"

class CaptureImageFilter : public BaseFilter {
    Q_OBJECT

public:
    explicit CaptureImageFilter(QObject* parent = nullptr);
    ~CaptureImageFilter();

    void processData();
    QString className() const {return "CaptureImageFilter";}
    FilterInstanceName objectInstance() const;

private:
    FilterInstanceName objectName_;
    static size_t objectCounter;
};
