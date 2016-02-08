#include "testwidget_2.h"
#include "ui_testwidget_2.h"

TestWidget_2::TestWidget_2(QWidget *parent) :
    QToolBox(parent),
    ui(new Ui::TestWidget_2)
{
    ui->setupUi(this);
}

TestWidget_2::~TestWidget_2()
{
    delete ui;
}
