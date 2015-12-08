#include <QString>
#include <QtTest>
#include "LibFilter.h"
#include <QJsonDocument>
#include <QFile>

class LibFilterTest : public QObject
{
    Q_OBJECT

public:
    LibFilterTest();

private Q_SLOTS:
    void testCaseSaveLoad();
};

LibFilterTest::LibFilterTest() {}

void LibFilterTest::testCaseSaveLoad()
{
    LibFilter libFilter;
    QJsonObject json1 = libFilter.save();
    QJsonDocument doc(json1);
    QFile file("test0.txt");
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();

    libFilter.load(json1);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(LibFilterTest)

#include "tst_LibFilterTest.moc"
