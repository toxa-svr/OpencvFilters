#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QString>
#include <QPixmap>

//-------------------------------------------------
// Unique identificator for filter classes
//-------------------------------------------------
typedef QString FilterId;


//-------------------------------------------------
// Filter description
//-------------------------------------------------
struct FilterDescription {
    FilterId id;
    QString name;
    QPixmap icon;
};




class BaseFilter;
typedef QWidget AbstractFilterWidget;

//-------------------------------------------------
// Result obtained from FilterFactory
//-------------------------------------------------
class FilterAndWidget {
public:
    FilterAndWidget(BaseFilter* filter, AbstractFilterWidget* filterWidget);
    //~FilterAndWidget();

    FilterAndWidget() = delete;
    FilterAndWidget(const FilterAndWidget&) = delete;
    FilterAndWidget& operator=(const FilterAndWidget&) = delete;

    BaseFilter* filter()                 {return filter_;}
    AbstractFilterWidget* filterWidget() {return filterWidget_;}
private:
    BaseFilter* filter_;
    AbstractFilterWidget* filterWidget_;
};





class FilterPluginInterface;

//-------------------------------------------------
// Filter factory
//-------------------------------------------------
class FilterFactory {
public:
    FilterFactory();

    FilterFactory(const FilterFactory&) = delete;
    FilterFactory& operator=(FilterFactory&) = delete;

    static FilterAndWidget createFilter(FilterId id);

    static QVector<FilterDescription> enumerateFilters();

private:
    static QVector<FilterPluginInterface*> interfaces;
};

#endif // FILTERFACTORY_H
