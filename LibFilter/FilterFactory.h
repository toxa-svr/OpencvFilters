#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include "FilterId.h"
#include "FilterAndWidget.h"
#include "FilterDescription.h"

class BaseFilter;

class FilterPluginInterface;

// Filter factory
class FilterFactory {
public:
    FilterFactory() = delete;
    FilterFactory(const FilterFactory&) = delete;
    FilterFactory& operator=(FilterFactory&) = delete;

    static FilterAndWidget createFilter(FilterId id);

    static QVector<FilterDescription> enumerateFilters();

private:
    static QVector<FilterPluginInterface*> interfaces;
};

#endif // FILTERFACTORY_H
