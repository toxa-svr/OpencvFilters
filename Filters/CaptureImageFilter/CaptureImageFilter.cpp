#include "CaptureImageFilter.h"
#include "FilterFactory.h"
//#include "capturewidget.h"
//#include "filter.h"
//#include "filterchain.h"

//#include "opencv2/core/mat.hpp"
//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>

// Делаем тип cv::Mat известным для QMetaType, чтобы его можно было поместить в QVariant
Q_DECLARE_METATYPE(cv::Mat)

size_t CaptureImageFilter::objectCounter = 0;

CaptureImageFilter::CaptureImageFilter(QObject* parent) :
    BaseFilter(parent)

  /*:
    FilterInterface(chain),
    sourceType(0),
    cameraNumber(0),
    curImage(0),
    emptyFrameW(640),
    emptyFrameH(480)*/
{
    objectName_ = className() + " " + QString::number(objectCounter);

    ++objectCounter;
    if (objectCounter == 0)
        throw std::runtime_error("Превышено максимальное количество объектов CaptureImageFilter");

    // TODO порты вывода
    FilterPortDescription description = {"Изображение", "cv::Mat"};
    FilterPortVector outPorts;
    outPorts.push_back(FilterPort(description));
    setOutPorts(outPorts);

    /*
    auto captureWidget = new CaptureWidget;
    widget = captureWidget;
    FilterInterface::setEnabled(false);
    connect(captureWidget, &CaptureWidget::sigEnabled, this, &CaptureImageFilter::setEnabled);
    connect(captureWidget, &CaptureWidget::sigRefreshPeriodMsChanged, this, &CaptureImageFilter::setRefreshPeriodMs);
    connect(captureWidget, &CaptureWidget::sigSourceTypeChanged, this, &CaptureImageFilter::setSourceType);
    connect(captureWidget, &CaptureWidget::sigCameraNumberChanged, this, &CaptureImageFilter::setCameraNumber);
    connect(captureWidget, &CaptureWidget::sigFile1NameChanged, this, &CaptureImageFilter::setFile1Name);
    connect(captureWidget, &CaptureWidget::sigFile2NameChanged, this, &CaptureImageFilter::setFile2Name);
    connect(captureWidget, &CaptureWidget::sigVideoFileNameChanged, this, &CaptureImageFilter::setVideoFileName);
    connect(captureWidget, &CaptureWidget::sigEmptyFrameWidthChanged, this, &CaptureImageFilter::setEmptyFrameWidth);
    connect(captureWidget, &CaptureWidget::sigEmptyFrameHeightChanged, this, &CaptureImageFilter::setEmptyFrameHeight);

    //signals from filter for widget
    connect(this, &CaptureImageFilter::updateWidgetEnabled, captureWidget, &CaptureWidget::updateWidget);
    connect(this, &CaptureImageFilter::updateWidgetVideoBar, captureWidget, &CaptureWidget::updateWidgetVideoBar);
    */
}

CaptureImageFilter::~CaptureImageFilter()
{
/*
    videoCapture.release();
    destroyWindow(filterName.toStdString());
    delete widget;
*/
}

//void CaptureImageFilter::setEnabled(bool enabled)
//{
/*
    switch (sourceType) {
        case 0: // camera
            if (enabled) {
                videoCapture.open(cameraNumber);
                //videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
                //videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 768);
                //videoCapture.set(CV_CAP_PROP_FPS, 30);

            }
            else {
                videoCapture.release();
            }
            break;

        case 1: // image
        break;

        case 2: // video
        if (enabled) {
            videoCapture.open(videoFileName.toStdString());
            //videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
            //videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 768);
            //videoCapture.set(CV_CAP_PROP_FPS, 30);
            framesTotal = videoCapture.get(CV_CAP_PROP_FRAME_COUNT);
            frameCounter = 0;
            emit updateWidgetVideoBar(frameCounter, framesTotal);
        }

        case 3: // empty
        break;
    }

    FilterInterface::setEnabled(enabled);
*/
//}

void CaptureImageFilter::processData() {
    cv::Mat frame;
#if 0
    switch (sourceType) {

        case 0: // camera
            if (videoCapture.isOpened()) {
                videoCapture >> frame;
            }
            break;

        case 1: // image
            if (curImage == 0 && file1Name.isEmpty() == false) {
                frame = imread(file1Name.toStdString());
                curImage = 1;
            }
            else if (curImage == 1 && file2Name.isEmpty() == false) {
                frame = imread(file2Name.toStdString());
                curImage = 0;
            }
            else if (file1Name.isEmpty() == false) {
                frame = imread(file1Name.toStdString());
            }
            else {
                frame.release();
            }
            break;

        case 2: // video
            if (videoCapture.isOpened()) {
                videoCapture >> frame;
                frameCounter++;
                emit updateWidgetVideoBar(frameCounter, framesTotal);
            }
            break;

        case 3: // empty
            frame.create(emptyFrameH, emptyFrameW, CV_8UC3);
            frame.setTo(Scalar(255,255,255));
            break;

    }

    // if no image read - stop capture
    if (!frame.data) {
        QMessageBox::warning(widget, "Error",
                             tr("No data in source image."),
                                 QMessageBox::Ok);
        isEnabled = false;
        emit updateWidgetEnabled(false);
    }
#endif
    FilterData filterData;
    filterData.setValue(frame);
    outPort(0)->setFilterData(filterData);
}

FilterInstanceName CaptureImageFilter::objectInstance() const {
    return objectName_;
}







