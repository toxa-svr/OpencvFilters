#ifndef FILTERPLUGININTERFACE
#define FILTERPLUGININTERFACE

class FilterAndWidget;
struct FilterDescription;

// Interface for all plugins
class FilterPluginInterface {
public:
    virtual ~FilterPluginInterface(){}
    virtual FilterAndWidget createFilter() const = 0;
    virtual FilterDescription description() const = 0;
};

#define FilterPluginInterface_iid "org.OpencvFilters.FilterPluginInterface"

Q_DECLARE_INTERFACE(FilterPluginInterface, FilterPluginInterface_iid)

#endif // FILTERPLUGININTERFACE

