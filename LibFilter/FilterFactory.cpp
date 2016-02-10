#include <QDir>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>
#include "FilterFactory.h"
#include "FilterPluginInterface.h"

QVector<FilterPluginInterface*> FilterFactory::interfaces;

FilterAndWidget FilterFactory::createFilter(FilterId id) {
    auto p = std::find_if(interfaces.cbegin(), interfaces.cend(), [&](const FilterPluginInterface* i) {
        return i->description().id  == id;
    });

    if (p == interfaces.cend())
        throw std::runtime_error("Cannot create filter (id not found)");

    return (*p)->createFilter();
}

QVector<FilterDescription> FilterFactory::enumerateFilters() {
    static QVector<FilterDescription> result;
    if (result.isEmpty()) {
        QDir pluginsDir(QCoreApplication::applicationDirPath());

//        #if defined(Q_OS_WIN)
//        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
//            pluginsDir.cdUp();

//        #elif defined(Q_OS_MAC)
//        if (pluginsDir.dirName() == "MacOS") {
//            pluginsDir.cdUp();
//            pluginsDir.cdUp();
//            pluginsDir.cdUp();
//        }
//        #endif

        pluginsDir.cd("plugins");

        qDebug() << "plugins path: " << pluginsDir.absolutePath();

        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject* plugin = pluginLoader.instance();
            if (plugin) {
                auto pluginInterface = qobject_cast<FilterPluginInterface*>(plugin);
                if (pluginInterface)
                    interfaces.push_back(pluginInterface);
            }
        }

        std::for_each(interfaces.cbegin(), interfaces.cend(), [&](const FilterPluginInterface* interface) {
            result.push_back(interface->description());
        });
    }
    return result;
}

