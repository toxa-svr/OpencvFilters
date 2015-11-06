#ifndef FILTERCHAIN_H
#define FILTERCHAIN_H


#include <QVector>
#include <QTimer>
#include "filterinterface.h"


class FilterChain : public QObject
{
    Q_OBJECT

private:

    // Chain of filters
    QVector<FilterInterface*> chain;
    unsigned int filterCounter;

    // Timer starts next frame processing
    QTimer timer;

    // Screenshot settings
    QString screenShotFilename;
    int screenShotCnt;
    bool isTakeScreenshot;
    int screenshotFilterIndex;

public:
    explicit FilterChain(QObject* parent = nullptr);
    ~FilterChain();

    // Filter chain editing
    void addFilter(FilterInterface* filter);
    void removeFilter(int index);
    void swapFilters(int i, int j);
    FilterInterface* getFilter(int i) {return chain[i];}
    void setInterval(int msec) {timer.start(msec);}
    unsigned int getCounter() {return filterCounter;}


    // Ask screenshot filename and set flag
//    void needScreenshot(int filterIndex);

    // Take screenshot from filter's output window
    // and save CV_8U single-channel JPG image
    // with default quality = 95
//    void takeScreenshot(const Mat & frame);


signals:
    // Measured times for each filter
    void elapsedTimesObtained(QVector<qint64> elapsedTimes);


private slots:
    // Current frame processing - Called by timer
    void processFrames();

};

#endif // FILTERCHAIN_H
