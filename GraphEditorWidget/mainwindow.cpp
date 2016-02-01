#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NodeEditorScene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);



    // Create NodeEditorScene and QGraphicsView for it
    nodeEditorScene = new NodeEditorScene(this);
    nodeEditorView = new QGraphicsView(nodeEditorScene);


    // Configure scene and connect singnals-slots for it
    nodeEditorScene->setStickyFocus(true); // clicking into the scene background will clear focus
    //connect(nodeEditorScene, SIGNAL(itemInserted(NodeItem*)), this, SLOT(itemInserted(NodeItem*)));
    //connect(nodeEditorScene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));


    // Configure view
    nodeEditorView->setRenderHint(QPainter::Antialiasing, true);
    nodeEditorView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    nodeEditorView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //nodeEditorView->scale(0.5, 0.5);
    //nodeEditorView->setBackgroundBrush(QPixmap(":/No-Ones-Laughing-3.jpg"));


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


    ui->dockWidget_2->setWidget(nodeEditorView);


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    nodeEditorScene->addItem(new NodeItem());
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_delButton_clicked()
{

}
