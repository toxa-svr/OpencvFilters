#pragma once

#include <QObject>
#include "FilterPluginInterface.h"

class DummyFilterPlugin : public QObject,  public FilterPluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.OpencvFilters.FilterPluginInterface" FILE "DummyFilter.json")
    Q_INTERFACES(FilterPluginInterface)

public:
    explicit DummyFilterPlugin(QObject* parent = nullptr);
    FilterAndWidget createFilter() const;
    FilterDescription description() const;
};
