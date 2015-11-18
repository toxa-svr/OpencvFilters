#include "opencv2/imgcodecs.hpp"
#include "CaptureImageFilter.h"

// We declare cv::Mat type to be known to QMetaType to use it in QVariant
Q_DECLARE_METATYPE(cv::Mat)

size_t CaptureImageFilter::instanceCounter = 0;

CaptureImageFilter::CaptureImageFilter(QObject* parent) :
    BaseFilter(parent)

{
    instanceName_ = className() + " " + QString::number(instanceCounter);

    ++instanceCounter;
    if (instanceCounter == 0)
        throw std::runtime_error("Maximum amount of CaptureImageFilter objects is exceeded");

    // TODO порты вывода
    FilterPortDescription description = {"Image", "cv::Mat"};
    FilterPortVector outPorts;
    outPorts.push_back(FilterPort(description));
    setOutPorts(outPorts);
}

CaptureImageFilter::~CaptureImageFilter() {}

void CaptureImageFilter::processData() {
    auto fileName = settings()["ImageFileName"].toString();
    cv::Mat frame = cv::imread(fileName.toStdString());
    FilterData filterData;
    filterData.setValue(frame);
    outPort(0)->setFilterData(filterData);
    setAlreadyProcessed();
}

FilterInstanceName CaptureImageFilter::instanceName() const {
    return instanceName_;
}







