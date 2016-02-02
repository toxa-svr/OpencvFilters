#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NodeEditorScene.h"
#include "NodeEditorView.h"
#include "testwidget_1.h"
#include "testwidget_2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);



    // Create NodeEditorScene and QGraphicsView for it
    nodeEditorScene = new NodeEditorScene(this);
    nodeEditorWidget = new NodeEditorWidget(nodeEditorScene, this);


    // Configure scene and connect singnals-slots for it
    nodeEditorScene->setStickyFocus(true); // clicking into the scene background will clear focus
    //connect(nodeEditorScene, SIGNAL(itemInserted(NodeItem*)), this, SLOT(itemInserted(NodeItem*)));
    //connect(nodeEditorScene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));


    // Create centralWidget for the window
    //   Create layout for the centralWidget
    //     Add QGraphicsView into layout
    //     Add toolbox into layout
//    QWidget *newCentralWidget = new QWidget(this);
//    QHBoxLayout *newLayout = new QHBoxLayout(this);
//    newLayout->addWidget(nodeEditorView);
//    //newLayout->addWidget(toolBox);
//    newCentralWidget->setLayout(newLayout);
//    setCentralWidget(newCentralWidget);


    ui->dockWidget_2->setWidget(nodeEditorWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    NodeItem * newItem = new NodeItem(nullptr);
    TestWidget_1 * newWidget = new TestWidget_1();
    newItem->setWidget(newWidget);
    nodeEditorScene->addItem(newItem);

    QPushButton * newBtn = new QPushButton("port in");
    NodePort * newPortIn = new NodePort(newItem, nodeEditorScene, newBtn, NodePort::In, NodePort::Left);

    QLabel * newLbl = new QLabel("port out");
    NodePort * newPortOut = new NodePort(newItem, nodeEditorScene, newLbl, NodePort::In, NodePort::Right);

    newItem->addPort(newPortIn);
    newItem->addPort(newPortOut);
}

void MainWindow::on_pushButton_2_clicked()
{
    NodeItem * newItem = new NodeItem(nullptr);
    testwidget_2 * newWidget = new testwidget_2();
    newItem->setWidget(newWidget);
    nodeEditorScene->addItem(newItem);
}

void MainWindow::on_delButton_clicked()
{

}
