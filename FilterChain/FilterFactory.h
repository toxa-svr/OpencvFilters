#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QString>
#include <QPixmap>

enum FilterId {

};

struct FilterDescription {
    FilterId id;
    QString name;
    QPixmap icon;
};

class AbstractFilter;
class AbstractFilterWidget;

class FilterAndWidget {
    FilterAndWidget(AbstractFilter* filter, AbstractFilterWidget* filterWidget);
    ~FilterAndWidget();
    AbstractFilter* filter()             {return filter_;}
    AbstractFilterWidget* filterWidget() {return filterWidget_;}
private:
    AbstractFilter* filter_;
    AbstractFilterWidget* filterWidget_;
};

class FilterFactory {
public:
    FilterFactory();
    FilterAndWidget createFilter(FilterId id);
    static FilterDescription enumerateFilters();
};

#endif // FILTERFACTORY_H
