#ifndef FILTERPORT_H
#define FILTERPORT_H

#include "FilterData.h"
#include "FilterPortDescription.h"

// Filter port class
class FilterPort {
public:
    FilterPort() {}
    explicit FilterPort(const FilterPortDescription& description);
    void setFilterData(const FilterData& filterData) {filterData_ = filterData;}
    FilterData filterData() const {return filterData_;}
    FilterPortDescription description() const {return description_;}

private:
    FilterData filterData_;
    FilterPortDescription description_;
};

#endif // FILTERPORT_H
