#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GraphEditorWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    GraphEditorWidget* newWidget = new GraphEditorWidget(this);
    newWidget->show();
    ui->dockWidget_2->setWidget(newWidget);



    newWidget->addNode();
    newWidget->addConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
}
