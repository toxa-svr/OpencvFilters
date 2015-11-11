#define _SCL_SECURE_NO_WARNINGS // disable warning about std::transform call

#include <QCoreApplication>
#include "FilterChain.h"
#if 0
FilterChain::FilterChain(QObject *parent) :
    QObject(parent),
    filterCounter(0)
//    screenShotCnt(0),
//    isTakeScreenshot(false)
{
    // Connect timer with frame processing start
    connect(&timer, &QTimer::timeout, this, &FilterChain::processFrames);
    timer.start(33);
}

FilterChain::~FilterChain(){
    std::for_each(chain.begin(), chain.end(), [&](FilterInterface* filter){delete filter;});
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void FilterChain::addFilter(FilterInterface* filter, const std::vector<FilterInterface*>& parents,
                            const std::vector<FilterInterface>& children)
{
    filterCounter++;
    chain.append((FilterInterface*const)filter);
    connect (filter , &FilterInterface::sigSetInterval, this, &FilterChain::setInterval);
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void FilterChain::removeFilter(int index)
{
    chain.remove(index);
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void FilterChain::swapFilters(int i, int j) {
    if (i>=0 && j>=0 && i!=j && i<chain.count() && j<chain.count()) {
        std::swap(chain[i], chain[j]);
    }
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void FilterChain::processFrames()
{
    ProcessDataContainer container;

    // check first capture filter is exist and enabled
    if (!chain.count())
        return;
    else if (!chain[0]->getEnabled())
        return;


    // process container by all filters
    for (int i = 0; i < chain.count();i++) {
        FilterInterface* filter = chain[i];

        try {
            // process data and get visualization frame (not stored in container)
            cv::Mat frameToShow = filter->run(container);

            // show or save output visualization frame
            if (frameToShow.data) {
                // show filter's output frame
                if (filter->getShowResult()) {
                    imshow(filter->getName().toStdString(), frameToShow);
                }
//                // save screenshot (if need) after frame processing
//                if (isTakeScreenshot && screenshotFilterIndex == i) {
//                    takeScreenshot(frameToShow);
//                }
            }
        }
        catch (std::runtime_error ex) {
//           // no required type in container
//           QMessageBox::warning(nullptr, "Warning",
//                                QString("No required type in container\nFilter ") +
//                                filter->getName() + QString(" will be disabled."),
//                                QMessageBox::Ok);
           filter->setEnabled(false);
        }
    }

    // show times
    QVector<qint64> elapsedTimes(chain.size());
    std::transform(chain.cbegin(), chain.cend(), elapsedTimes.begin(), [&](FilterInterface* filter){
        return filter->timeElapsed();
    });
    // signal to mainwindow with times array
    emit elapsedTimesObtained(elapsedTimes);
}




//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
/* DONT USE GUI!!!
void FilterChain::takeScreenshot(const Mat & frame)
{
    isTakeScreenshot = false;

    if (screenShotFilename.isEmpty()){
//        QMessageBox::warning(parent, "Warning",
//                             tr("There is no filename to save screensot\n"),
//                             QMessageBox::Ok);
        return;
    }
   if (!frame.data) {
//       QMessageBox::warning(parent, "Warning",
//                            tr("There is no data in the filter's output frame\n"),
//                            QMessageBox::Ok);
       return;
   }

   // create full filename with counter
   QString fullname = screenShotFilename + "_" + QString::number(screenShotCnt) + ".jpg";
   screenShotCnt++;

   // check format
   //   Only 8-bit (or CV_16U in case of PNG, JPEG 2000, and TIFF)
   //   single-channel or 3-channel (with ‘BGR’ channel order) images can be
   //   saved using imwrite function.
   Mat screenshotFrame;
   if (frame.depth() != CV_8U) {
       frame.convertTo(screenshotFrame, CV_8U);
   } else {
       screenshotFrame = frame;
   }
   if (screenshotFrame.channels()!= 1) {
       cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
   }

   // save image
   imwrite(fullname.toStdString(), screenshotFrame);
}
*/


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
/* DONT USE GUI!!!
void FilterChain::needScreenshot(int filterIndex)
{
    // get path for screenshots
    if (screenShotFilename.isEmpty()) {
        screenShotFilename = QFileDialog::getSaveFileName(nullptr,
                                                "Save screenshot",
                                                QCoreApplication::applicationDirPath(),
                                                          "JPG (*.jpg);;All files (*.*)");
        if (screenShotFilename.isEmpty()) {
            QMessageBox::warning(nullptr, "Warning",
                                 tr("There is no filename to save screensot\n"),
                                 QMessageBox::Ok);
            return;
        }
    }
    screenshotFilterIndex = filterIndex;
    isTakeScreenshot = true;
}
*/
#endif
