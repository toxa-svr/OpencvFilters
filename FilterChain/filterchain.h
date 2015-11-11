#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

//#include <QTimer>
#include "AbstractFilter.h"
//#include "digraph.hpp"

class DataToShow {};

class FilterChain : public QObject {
    Q_OBJECT

public:
    explicit FilterChain(QObject* parent = nullptr);
    FilterChain(const FilterChain&) = delete;
    FilterChain& operator=(const FilterChain&) = delete;
    ~FilterChain();

    // Функции изменения графа фильтров
    void addFilter   (AbstractFilter* filter);
    void removeFilter(FilterObjectName objectName);
    void addLink     (FilterObjectName filterFrom, PortIndex portFrom, FilterObjectName filterTo, PortIndex portTo);
    void removeLink  (FilterObjectName filterFrom, PortIndex portFrom, FilterObjectName filterTo, PortIndex portTo);

    // Функции для получения данных для отображения
    void addDataToShow   (FilterObjectName filterFrom, PortIndex portFrom);
    void removeDataToShow(FilterObjectName filterFrom, PortIndex portFrom);
    DataToShow dataToShow(FilterObjectName filterFrom, PortIndex portFrom) const;

    void processFilters();
};

#endif // FILTERCHAIN_H
