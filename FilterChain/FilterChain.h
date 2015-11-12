#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H

#include <QVector>
#include <QMap>
#include "AbstractFilter.h"

struct FullPortAddress {
    FilterObjectName filter;
    PortIndex port;
};

// Структура описывает связь между фильтрами
struct FilterLink {
    FullPortAddress from;
    FullPortAddress to;
};

bool operator==(const FilterLink& lhs, const FilterLink& rhs);
bool operator!=(const FilterLink& lhs, const FilterLink& rhs);

bool operator==(const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator!=(const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator< (const FullPortAddress& lhs, const FullPortAddress& rhs);
bool operator> (const FullPortAddress& lhs, const FullPortAddress& rhs);


// Цепочка (граф) фильтров.
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
    void addLink     (const FilterLink& filterLink);
    void removeLink  (const FilterLink& filterLink);

    // Функции для получения данных для отображения
    void addDataToShow   (const FullPortAddress& from);
    void removeDataToShow(const FullPortAddress& from);
    FilterData dataToShow(const FullPortAddress& from) const;

    void processFilters();

private:
    int findFilterIndex(FilterObjectName objectName);

    QVector<AbstractFilter*> filters;
    QVector<FilterLink> links;
    QVector<FullPortAddress> dataToShowAddressVector;
    QMap<FullPortAddress, FilterData> dataToShowMap;
};

#endif // FILTERCHAIN_H
