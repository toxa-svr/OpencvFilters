#ifndef TESTWIDGET_2_H
#define TESTWIDGET_2_H

#include <QToolBox>

namespace Ui {
class testwidget_2;
}

class testwidget_2 : public QToolBox
{
    Q_OBJECT

public:
    explicit testwidget_2(QWidget *parent = 0);
    ~testwidget_2();

private:
    Ui::testwidget_2 *ui;
};

#endif // TESTWIDGET_2_H
