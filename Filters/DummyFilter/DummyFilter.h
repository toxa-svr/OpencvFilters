#pragma once

#include "BaseFilter.h"

class DummyFilter : public BaseFilter {
    Q_OBJECT

public:
    explicit DummyFilter(QObject* parent = nullptr);
    ~DummyFilter();

    void processData();
    QString className() const {return "CaptureImageFilter";}
    FilterInstanceName instanceName() const override;

private:
    FilterInstanceName instanceName_;
    static size_t instanceCounter;
};
