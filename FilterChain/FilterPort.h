#ifndef FILTERPORT_H
#define FILTERPORT_H

#include "FilterData.h"

class FilterPortDescription {};

class FilterPort {
public:
    FilterPort();
    void setFilterData(const FilterData& filterData) {filterData_ = filterData;}
    FilterData filterData() const {return filterData_;}
    FilterPortDescription description() const;

private:
    FilterData filterData_;
};

#endif // FILTERPORT_H
