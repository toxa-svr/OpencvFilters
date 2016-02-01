#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NodeEditorWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    GraphEditorWidget* graphWidget = new GraphEditorWidget(this);
    graphWidget->show();
    ui->dockWidget_2->setWidget(graphWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    graphWidget->addNode();
}

void MainWindow::on_pushButton_2_clicked()
{
    graphWidget->addNode();
}

void MainWindow::on_delButton_clicked()
{

}
