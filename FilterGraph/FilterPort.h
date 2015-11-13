#ifndef FILTERPORT_H
#define FILTERPORT_H

#include "FilterData.h"

// Description of a filter port
struct FilterPortDescription {
    QString name;
    QString type;
};

// Filter port class
class FilterPort {
public:
    FilterPort() {}
    FilterPort(const FilterPortDescription& description);
    void setFilterData(const FilterData& filterData) {filterData_ = filterData;}
    FilterData filterData() const {return filterData_;}
    FilterPortDescription description() const {return description_;}

private:
    FilterData filterData_;
    FilterPortDescription description_;
};

#endif // FILTERPORT_H
