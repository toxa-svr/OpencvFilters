#ifndef CAPTUREIMAGEFILTERPLUGIN
#define CAPTUREIMAGEFILTERPLUGIN

#include <QObject>
#include "FilterPluginInterface.h"

class CaptureImageFilterPlugin : public QObject,  public FilterPluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.OpencvFilters.FilterPluginInterface" FILE "CaptureImageFilter.json")
    Q_INTERFACES(FilterPluginInterface)

public:
    CaptureImageFilterPlugin(QObject* parent = nullptr);
    FilterAndWidget createFilter() const;
    FilterDescription description() const;
};

//#define FilterPluginInterface_iid "org.OpencvFilters.FilterPluginInterface"
//Q_DECLARE_INTERFACE(FilterPluginInterface, FilterPluginInterface_iid)

#endif // CAPTUREIMAGEFILTERPLUGIN

