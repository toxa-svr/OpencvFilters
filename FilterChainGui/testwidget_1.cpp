#include "testwidget_1.h"
#include "ui_testwidget_1.h"

TestWidget_1::TestWidget_1(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::TestWidget_1)
{
    ui->setupUi(this);
}

TestWidget_1::~TestWidget_1()
{
    delete ui;
}
