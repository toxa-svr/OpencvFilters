#ifndef TESTWIDGET_1_H
#define TESTWIDGET_1_H

#include <QGroupBox>

namespace Ui {
class TestWidget_1;
}

class TestWidget_1 : public QGroupBox
{
    Q_OBJECT

public:
    explicit TestWidget_1(QWidget *parent = 0);
    ~TestWidget_1();

private:
    Ui::TestWidget_1 *ui;
};

#endif // TESTWIDGET_1_H
