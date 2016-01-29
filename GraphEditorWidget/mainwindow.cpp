#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GraphEditorWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    GraphEditorWidget* graphWidget = new GraphEditorWidget(this);
    graphWidget->show();
    ui->dockWidget_2->setWidget(graphWidget);



    QPushButton button("Button", this);
    button.setVisible(true);


    graphWidget->addNode();
    graphWidget->addNode();
    graphWidget->addNode();
    graphWidget->addConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
}
