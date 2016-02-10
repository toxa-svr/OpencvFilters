#include "CaptureImageFilter.h"
#include "CaptureImageWidget.h"
#include "CaptureImageFilterPlugin.h"
#include "FilterFactory.h"

CaptureImageFilterPlugin::CaptureImageFilterPlugin(QObject* parent) : QObject(parent) {}

FilterAndWidget CaptureImageFilterPlugin::createFilter() const {
    auto filter = new CaptureImageFilter;
    auto widget = new CaptureImageWidget;
    return FilterAndWidget(filter, widget);
}

FilterDescription CaptureImageFilterPlugin::description() const {
    FilterDescription result;
    result.icon = QPixmap();              // TODO добавить иконку
    result.id = static_cast<FilterId>(1); // TODO откуда брать значение?
    result.name = "Capture image filter";

    FilterPortDescription description = {"Image", "cv::Mat"};
    result.outputs.push_back(description);
    return result;
}
