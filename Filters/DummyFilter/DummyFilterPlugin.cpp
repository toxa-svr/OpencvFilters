#include "DummyFilter.h"
#include "DummyWidget.h"
#include "DummyFilterPlugin.h"
#include "FilterFactory.h"

DummyFilterPlugin::DummyFilterPlugin(QObject* parent) : QObject(parent) {}

FilterAndWidget DummyFilterPlugin::createFilter() const {
    auto filter = new DummyFilter;
    auto widget = new DummyWidget;
    return FilterAndWidget(filter, widget);
}

FilterDescription DummyFilterPlugin::description() const {
    FilterDescription result;
    result.icon = QPixmap();              // TODO добавить иконку
    result.id = static_cast<FilterId>(1); // TODO откуда брать значение?
    result.name = "Dummy filter";
    return result;
}
