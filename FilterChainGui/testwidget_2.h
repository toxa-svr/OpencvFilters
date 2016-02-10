#ifndef TESTWIDGET_2_H
#define TESTWIDGET_2_H

#include <QToolBox>

namespace Ui {
class TestWidget_2;
}

class TestWidget_2 : public QToolBox
{
    Q_OBJECT

public:
    explicit TestWidget_2(QWidget *parent = 0);
    ~TestWidget_2();

private:
    Ui::TestWidget_2 *ui;
};

#endif // TESTWIDGET_2_H
