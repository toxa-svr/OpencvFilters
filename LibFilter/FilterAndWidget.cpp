#include "FilterAndWidget.h"
#include "BaseFilter.h"

FilterAndWidget::FilterAndWidget(BaseFilter* filter, AbstractFilterWidget* filterWidget) : filter_(filter),
    filterWidget_(filterWidget) {}

FilterAndWidget::~FilterAndWidget()  {}

//FilterAndWidget::FilterAndWidget(const FilterAndWidget&);
//FilterAndWidget& FilterAndWidget::operator=(const FilterAndWidget&);

FilterAndWidget::FilterAndWidget(FilterAndWidget&& other) :
    filter_(std::move(other.filter())),  filterWidget_(std::move(other.filterWidget_))
{}

FilterAndWidget& FilterAndWidget::operator=(FilterAndWidget&& rhs) {
    this->filter_ = std::move(rhs.filter_);
    this->filterWidget_ = std::move(rhs.filterWidget_);
    return *this;
}

BaseFilter* FilterAndWidget::filter() const {
    return filter_.get();
}

AbstractFilterWidget* FilterAndWidget::filterWidget() const {
    return filterWidget_.get();
}

