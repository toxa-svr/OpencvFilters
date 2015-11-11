#include "capturefilter.h"
#include "capturewidget.h"
#include "filter.h"
#include "filterchain.h"

#include <QElapsedTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


CaptureFilter::CaptureFilter(QObject *parent)/*:
    FilterInterface(chain),
    sourceType(0),
    cameraNumber(0),
    curImage(0),
    emptyFrameW(640),
    emptyFrameH(480)*/
{
    /*
    filterName = "Capture_" + QString::number(chain->getCounter());
    auto captureWidget = new CaptureWidget;
    widget = captureWidget;
    FilterInterface::setEnabled(false);
    connect(captureWidget, &CaptureWidget::sigEnabled, this, &CaptureFilter::setEnabled);
    connect(captureWidget, &CaptureWidget::sigRefreshPeriodMsChanged, this, &CaptureFilter::setRefreshPeriodMs);
    connect(captureWidget, &CaptureWidget::sigSourceTypeChanged, this, &CaptureFilter::setSourceType);
    connect(captureWidget, &CaptureWidget::sigCameraNumberChanged, this, &CaptureFilter::setCameraNumber);
    connect(captureWidget, &CaptureWidget::sigFile1NameChanged, this, &CaptureFilter::setFile1Name);
    connect(captureWidget, &CaptureWidget::sigFile2NameChanged, this, &CaptureFilter::setFile2Name);
    connect(captureWidget, &CaptureWidget::sigVideoFileNameChanged, this, &CaptureFilter::setVideoFileName);
    connect(captureWidget, &CaptureWidget::sigEmptyFrameWidthChanged, this, &CaptureFilter::setEmptyFrameWidth);
    connect(captureWidget, &CaptureWidget::sigEmptyFrameHeightChanged, this, &CaptureFilter::setEmptyFrameHeight);

    //signals from filter for widget
    connect(this, &CaptureFilter::updateWidgetEnabled, captureWidget, &CaptureWidget::updateWidget);
    connect(this, &CaptureFilter::updateWidgetVideoBar, captureWidget, &CaptureWidget::updateWidgetVideoBar);
    */
}

CaptureFilter::~CaptureFilter()
{
/*
    videoCapture.release();
    destroyWindow(filterName.toStdString());
    delete widget;
*/
}

//void CaptureFilter::setEnabled(bool enabled)
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

void CaptureFilter::processData()
{
/*
    Mat frame;
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


    // insert new frame into container
    input.push_back(frame);
    return frame;
*/
}








