#ifndef FILTERANDWIDGET
#define FILTERANDWIDGET

#include <memory>
#include "AbstractFilterWidget.h"

class BaseFilter;

// Result obtained from FilterFactory
class FilterAndWidget {
public:
    FilterAndWidget(BaseFilter* filter, AbstractFilterWidget* filterWidget);
    ~FilterAndWidget();

    //FilterAndWidget() = delete;
    FilterAndWidget(const FilterAndWidget&) = delete;
    FilterAndWidget& operator=(const FilterAndWidget&) = delete;
    FilterAndWidget(FilterAndWidget&&);
    FilterAndWidget& operator=(FilterAndWidget&&);

    BaseFilter* filter() const;
    AbstractFilterWidget* filterWidget() const;

private:
    std::unique_ptr<BaseFilter> filter_;
    std::unique_ptr<AbstractFilterWidget> filterWidget_;
    //BaseFilter* filter_;
    //AbstractFilterWidget* filterWidget_;
};

#endif // FILTERANDWIDGET

