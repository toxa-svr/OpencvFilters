#include <QJsonArray>
#include "FilterFactory.h"
#include "LibFilter.h"

LibFilter::LibFilter() {
    filterGraph = std::make_unique<FilterGraph>();
}

QVector<FilterDescription> LibFilter::enumerateFilters() const {
    return FilterFactory::enumerateFilters();
}

LibFilter::CreateFilterResult LibFilter::createFilter(FilterId id) {
    faws.push_back(FilterFactory::createFilter(id));
    filterGraph->addFilter(faws.back().filter());
    CreateFilterResult result = {faws.back().filterWidget(), faws.back().filter()->instanceName()};
    return result;
}

void LibFilter::removeFilter(FilterInstanceName instanceName) {
    filterGraph->removeFilter(instanceName);
    auto pend = std::remove_if(faws.begin(), faws.end(), [&](FilterAndWidget& faw) {
        return faw.filter()->instanceName() == instanceName;
    });
    faws.erase(pend, faws.end());
}

// Functions to modify data links between filters
void LibFilter::addLink(const FilterLink& filterLink) {
    filterGraph->addLink(filterLink);
}

void LibFilter::removeLink(const FilterLink& filterLink) {
    filterGraph->removeLink(filterLink);
}

QVector<FilterLink> LibFilter::links() const {
    return filterGraph->links();
}

// Functions to get image data
void LibFilter::addDataToShow(const FullPortAddress& from) {
    filterGraph->addDataToShow(from);
}

void LibFilter::removeDataToShow(const FullPortAddress& from) {
    filterGraph->removeDataToShow(from);
}

FilterData LibFilter::dataToShow(const FullPortAddress& from) const {
    return filterGraph->dataToShow(from);
}

QVector<FullPortAddress> LibFilter::dataToShowInfo() const {
    return filterGraph->dataToShowInfo();
}

void LibFilter::processFilters() {
    filterGraph->processFilters();
}

QJsonObject LibFilter::save() const {
    QJsonObject jsonObject;

    QJsonArray linksArray;
    const auto&& links = filterGraph->links();
    std::for_each(links.cbegin(), links.cend(), [&](const FilterLink& value) {
        QJsonObject link;
        link["from_filter"] = value.from.filter;
        link["from_port"]   = value.from.port;
        link["to_filter"]   = value.to.filter;
        link["to_port"]     = value.to.port;
        linksArray.append(link);
    });
    jsonObject["links"] = linksArray;

    QJsonArray dataToShowArray;
    const auto&& dataToShowVector = filterGraph->dataToShowInfo();
    std::for_each(dataToShowVector.cbegin(), dataToShowVector.cend(), [&](const FullPortAddress& value) {
        QJsonObject dataToShow;
        dataToShow["filter"] = value.filter;
        dataToShow["port"]   = value.port;
        dataToShowArray.append(dataToShow);
    });
    jsonObject["dataToShow"] = dataToShowArray;

    QJsonArray fawArray;
    std::for_each(faws.cbegin(), faws.cend(), [&](const FilterAndWidget& faw) {
        QJsonObject fawJson;
        fawJson["instanceName"] = faw.filter()->instanceName();
        fawJson["filterId"] = faw.filter()->filterId();
        QJsonObject fawSettings;
        const auto&& settings = faw.filter()->settings();
        for (auto i = settings.cbegin(); i != settings.cend(); ++i) {
            fawSettings[i.key()] = i.value().toJsonValue();
        }

        fawJson["settings"] = fawSettings;
        fawArray.append(fawJson);

    });
    jsonObject["faws"] = fawArray;

    return jsonObject;
}

void LibFilter::load(const QJsonObject& jsonObject) {
    filterGraph = std::make_unique<FilterGraph>();
    faws.clear();
    QMap<FilterInstanceName, FilterInstanceName> instanceNameMap; // <saved instance, new instance>

    const QJsonArray fawArray = jsonObject["faws"].toArray();

    std::for_each(fawArray.constBegin(), fawArray.constEnd(), [&](const QJsonValue& value) {
        QJsonObject fawJson = value.toObject();
        FilterInstanceName instanceName = fawJson["instanceName"].toString();
        FilterId filterId = fawJson["filterId"].toString();
        auto faw = FilterFactory::createFilter(filterId);
        QJsonObject fawSettings = fawJson["settings"].toObject();
        FilterSettings settings;
        for (auto i = fawSettings.constBegin(); i != fawSettings.constEnd(); ++i) {
            settings[i.key()] = i.value();
        }
        faw.filter()->setSettings(settings);
        instanceNameMap[instanceName] = faw.filter()->instanceName();
        filterGraph->addFilter(faw.filter());
    });

    const QJsonArray linksArray = jsonObject["links"].toArray();
    std::for_each(linksArray.constBegin(), linksArray.constEnd(), [&](const QJsonValue& value) {
        QJsonObject link = value.toObject();
        FilterLink filterLink;
        filterLink.from.filter = instanceNameMap[link["from_filter"].toString()];
        filterLink.from.port   = link["from_port"].toInt();
        filterLink.to.filter   = instanceNameMap[link["to_filter"].toString()];
        filterLink.to.port     = link["to_port"].toInt();
        filterGraph->addLink(filterLink);
    });

    const QJsonArray dataToShowArray = jsonObject["dataToShow"].toArray();
    std::for_each(dataToShowArray.constBegin(), dataToShowArray.constEnd(), [&](const QJsonValue& value) {
        QJsonObject fpaObject = value.toObject();
        FullPortAddress fpa;
        fpa.filter = instanceNameMap[fpaObject["filter"].toString()];
        fpa.port   = fpaObject["port"].toInt();
        filterGraph->addDataToShow(fpa);
    });
}
