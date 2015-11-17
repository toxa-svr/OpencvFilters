#include <QString>
#include <QtTest>

#include <QUuid>

#include "FilterGraph.h"

// Dummy filter for FilterGraphTests test purposes
// It just retransmits input(i) to output(i) if the corresponding input port exists or i otherwise
class DummyFilter : public BaseFilter {
public:
    DummyFilter(int inPorts, int outPorts);
    virtual void processData();
    virtual QString className() const {return "DummyFilter";}
    virtual FilterInstanceName instanceName() {return name;}
private:
    int inPortsAmount;
    int outPortsAmount;
    FilterInstanceName name;
};

DummyFilter::DummyFilter(int inPorts, int outPorts) : inPortsAmount(inPorts), outPortsAmount(outPorts),
    name(QUuid::createUuid().toString())
{
    FilterPortVector inPortsVector(inPorts);
    setInPorts(inPortsVector);
    FilterPortVector outPortsVector(outPorts);
    setOutPorts(outPortsVector);
}

void DummyFilter::processData() {
    for (int i = 0; i < std::min(inPortsAmount, outPortsAmount); ++i)
        outPort(i)->setFilterData(inPort(i)->filterData());
    for (int i = std::min(inPortsAmount, outPortsAmount); i < outPortsAmount; ++i)
        outPort(i)->setFilterData(FilterData(QString::number(i)));
    setAlreadyProcessed();
}

class FilterGraphTestsTest : public QObject
{
    Q_OBJECT

public:
    FilterGraphTestsTest();

private Q_SLOTS:
    void testCaseSimpleNetwork();
};

FilterGraphTestsTest::FilterGraphTestsTest()
{
}

void FilterGraphTestsTest::testCaseSimpleNetwork()
{
    DummyFilter dummyFilter1(0, 2);
    DummyFilter dummyFilter2(0, 2);
    DummyFilter dummyFilter3(2, 2);
    DummyFilter dummyFilter4(2, 2);
    DummyFilter dummyFilter5(2, 0);
    DummyFilter dummyFilter6(2, 0);
    BaseFilter* filters[6] = {&dummyFilter1, &dummyFilter2, &dummyFilter3, &dummyFilter4, &dummyFilter5, &dummyFilter6};
    FilterGraph filterGraph;
    for (int i = 0; i < 6; ++i) {
        filterGraph.addFilter(filters[i]);
        //qDebug() << "filter" << i << ": name " << filters[i]->instanceName();
    }

    FilterLink links[8] = {
        {{dummyFilter1.instanceName(), 0}, {dummyFilter3.instanceName(), 0}},
        {{dummyFilter1.instanceName(), 1}, {dummyFilter4.instanceName(), 0}},
        {{dummyFilter2.instanceName(), 0}, {dummyFilter4.instanceName(), 1}},
        {{dummyFilter2.instanceName(), 1}, {dummyFilter3.instanceName(), 1}},
        {{dummyFilter3.instanceName(), 0}, {dummyFilter5.instanceName(), 0}},
        {{dummyFilter3.instanceName(), 1}, {dummyFilter6.instanceName(), 1}},
        {{dummyFilter4.instanceName(), 0}, {dummyFilter5.instanceName(), 1}},
        {{dummyFilter4.instanceName(), 1}, {dummyFilter6.instanceName(), 0}}
    };

    for (int i = 0; i < 8; ++i)
        filterGraph.addLink(links[i]);

    FullPortAddress address1 = {dummyFilter1.instanceName(), 1};
    FullPortAddress address2 = {dummyFilter4.instanceName(), 0};
    filterGraph.addDataToShow(address1);
    filterGraph.addDataToShow(address2);

    //qDebug() << "now process filters";
    filterGraph.processFilters();
    //qDebug() << "now show data";

    auto data1 = filterGraph.dataToShow(address1);
    auto data2 = filterGraph.dataToShow(address2);

    for (int i = 0; i < 6; ++i)
        filterGraph.removeFilter(filters[i]->instanceName());
    for (int i = 0; i < 8; ++i)
        filterGraph.removeLink(links[i]);
    filterGraph.removeDataToShow(address1);
    filterGraph.removeDataToShow(address2);

    filterGraph.processFilters();

    QVERIFY(data1.toString() == "1");
    QVERIFY(data2.toString() == "1");
}

QTEST_APPLESS_MAIN(FilterGraphTestsTest)

#include "tst_FilterGraphTestsTest.moc"
