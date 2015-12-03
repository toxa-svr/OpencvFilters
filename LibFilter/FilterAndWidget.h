#ifndef FILTERANDWIDGET
#define FILTERANDWIDGET

class BaseFilter;
class AbstractFilterWidget;

// Result obtained from FilterFactory
class FilterAndWidget {
public:
    FilterAndWidget(BaseFilter* filter, AbstractFilterWidget* filterWidget);
    ~FilterAndWidget();

    FilterAndWidget() = delete;
    FilterAndWidget(const FilterAndWidget&) = delete;
    FilterAndWidget& operator=(const FilterAndWidget&) = delete;

    BaseFilter* filter()                 {return filter_;}
    AbstractFilterWidget* filterWidget() {return filterWidget_;}
private:
    BaseFilter* filter_;
    AbstractFilterWidget* filterWidget_;
};

#endif // FILTERANDWIDGET

