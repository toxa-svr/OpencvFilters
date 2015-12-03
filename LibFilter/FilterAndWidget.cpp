#include "FilterAndWidget.h"

FilterAndWidget::FilterAndWidget(BaseFilter* filter, AbstractFilterWidget* filterWidget) : filter_(filter),
    filterWidget_(filterWidget) {}

FilterAndWidget::~FilterAndWidget() {
    delete filter_;
    delete filterWidget_;
}
