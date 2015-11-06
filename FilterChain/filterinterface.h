#ifndef FILTERINTERFACE_H
#define FILTERINTERFACE_H

#ifndef Q_MOC_RUN
#include <boost/any.hpp>
#endif

#include <QtCore>
#include <QElapsedTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
class FilterChain;

typedef std::vector<boost::any> ProcessDataContainer;

template<typename T>
T& selectProcessData(ProcessDataContainer& container) {

    for (size_t i = 0; i < container.size(); ++i) {
        if (container[i].type() == typeid(T))
            return boost::any_cast<T>(container[i]);
    }
    throw std::runtime_error("No required type in container");
}

class FilterInterface : public QObject
{
    Q_OBJECT

public:
    FilterInterface(FilterChain *chain) :
        filterChain(chain),
        isEnabled(true),
        showResult(true),
        widget(nullptr),
        timeElapsed_(0) {}


    // run filter
    // (processe data stored in container, measure time, return visualization frame)
    Mat run(ProcessDataContainer& container) {
        if (!isEnabled) {
            setTimeElapsed(0);
            return Mat();
        }
        QElapsedTimer timer;
        timer.start();

        // processing can modify data, stored in container
        //     this data will be processed by next filters
        // processing output is frame for visualization only (not stored in container)
        Mat frameToShow = processFrame(container);

        setTimeElapsed(timer.elapsed());

        return frameToShow;
    }


    // process data stored in container by filter
    // filter can add/modify elements of container
    // filter output frame is a frame for visualization only (frameToShow)
    virtual Mat processFrame(ProcessDataContainer& input) = 0;


    void setName(const QString &name) {filterName = name;}
    QString getName()    const {return filterName;}
    bool getEnabled()    const {return isEnabled;}
    bool getShowResult() const {return showResult;}
    QWidget* getWidget() const {return widget;}
    qint64 timeElapsed() const {return timeElapsed_;}

signals:
    void sigSetInterval(int); // change frame rate
    void updateWidgetEnabled(bool);     // signal to widget about enable-disable filter
    void updateWidgetShowResult(bool);  // signal to widget about enable-disable visualization

public slots:

    void setShowResult(bool val) {
        showResult = val;
        checkWindowsToClose();
        emit updateWidgetShowResult(val);
    }

    virtual void setEnabled(bool val) {
        isEnabled = val;
        checkWindowsToClose();
        emit updateWidgetEnabled(val);
    }

protected:
    void setTimeElapsed(qint64 time) {timeElapsed_ = time;}

    FilterChain* filterChain;
    unsigned int myindex;
    QString filterName;
    QWidget* widget;

    bool isEnabled;         // use filter in filterchain
    bool showResult;        // show visualization frame

private:
    void checkWindowsToClose() { // Close visualization frame windows if filter is disabled
        if (!isEnabled || !showResult)
            destroyWindow(filterName.toStdString());
    }

    quint64 timeElapsed_;
};

#endif // FILTERINTERFACE_H
