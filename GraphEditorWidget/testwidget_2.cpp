#include "testwidget_2.h"
#include "ui_testwidget_2.h"

testwidget_2::testwidget_2(QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::testwidget_2)
{
    ui->setupUi(this);
}

testwidget_2::~testwidget_2()
{
    delete ui;
}
