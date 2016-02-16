#include <QDesktopServices>
#include "MainWindow.h"

#include "LibFilter.h"
#include "NodeEditorScene.h"
#include "NodeEditorWidget.h"
#include "NodeItemProxy.h"
#include "testwidget_1.h"
#include "testwidget_2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qApp->setStyle("Fusion");

    setWindowTitle(tr("OpenCV FilterChain GUI v0.1"));
    setMinimumSize(640, 480);
    resize(640, 480);

    // Create status bar
    statusBar()->setEnabled(true);
    statusBar()->setVisible(true);



    // Create actions and put them into MenuBar, ToolBars, ToolBoxes
    createActions();
    createMenus();
    createToolbars();
    createToolBox();


    // Create NodeEditorScene and QGraphicsView for it
    nodeEditorScene = new NodeEditorScene(this);
    nodeEditorWidget = new NodeEditorWidget(nodeEditorScene, this);

    // Configure scene and connect singnals-slots for it
    nodeEditorScene->setSceneRect(QRectF(0, 0, 5000, 5000));
    //connect(nodeEditorScene, SIGNAL(itemInserted(NodeItem*)), this, SLOT(itemInserted(NodeItem*)));
    //connect(nodeEditorScene, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(itemSelected(QGraphicsItem*)));


    // Create centralWidget for the window
    //   Create layout for the centralWidget
    //     Add QGraphicsView into layout
    //     Add toolbox into layout
    QHBoxLayout *newLayout = new QHBoxLayout();
    newLayout->addWidget(nodeEditorWidget);
    //newLayout->addWidget(toolBox);

    QWidget *newCentralWidget = new QWidget();
    newCentralWidget->setLayout(newLayout);

    setCentralWidget(newCentralWidget);



    // TODO next - read settings for main window and graph editor
    // TODO next - open the last used file
    //nodeEditorWidget.setSettings();

}

MainWindow::~MainWindow()
{

}



//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void MainWindow::createActions()
{
    // Menu-File
    fileNewAction = new QAction(tr("&New"), this);
    fileNewAction->setShortcut(tr("Ctrl+N"));
    fileNewAction->setStatusTip(tr("Create new file"));
    connect(fileNewAction, SIGNAL(triggered()), this, SLOT(fileNew()));

    fileOpenAction = new QAction(tr("&Open"), this);
    fileOpenAction->setShortcut(tr("Ctrl+O"));
    fileOpenAction->setStatusTip(tr("Open existing new file"));
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()));

    fileSaveAction = new QAction(tr("&Save"), this);
    fileSaveAction->setShortcut(tr("Ctrl+S"));
    fileSaveAction->setStatusTip(tr("Save file"));
    connect(fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()));

    fileSaveAsAction = new QAction(tr("Save As"), this);
    fileSaveAsAction->setStatusTip(tr("Save as a new file"));
    connect(fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+X"));
    exitAction->setStatusTip(tr("Quit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Menu-Edit
    // Get available filters
    QVector<FilterDescription> filterList = libFilter.enumerateFilters();
    foreach(FilterDescription nextFilter, filterList) {
        qDebug() << nextFilter.id << nextFilter.name;
        QAction * newAddAction = new QAction(nextFilter.name, this);
        newAddAction->setData(nextFilter.id);
        newAddAction->setStatusTip(tr("Add new filter ") + newAddAction->text() + tr(" ID:") + newAddAction->data().toString());
        connect(newAddAction, SIGNAL(triggered()), this, SLOT(addItem()));
        addItemActionVector.append(newAddAction);
    }

    // TODO
    // Add one test item
    QAction * testAddAction = new QAction("Test item", this);
    testAddAction->setData("000");
    testAddAction->setStatusTip(tr("Test item ID:") + testAddAction->data().toString());
    connect(testAddAction, SIGNAL(triggered()), this, SLOT(addItem()));
    addItemActionVector.append(testAddAction);


    deleteItemAction = new QAction(tr("Delete"), this);
    deleteItemAction->setShortcut(tr("Delete"));
    deleteItemAction->setStatusTip(tr("Delete filter from graph"));
    connect(deleteItemAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    // Menu-Debug
    debugDrawAction = new QAction(tr("Debug draw"), this);
    debugDrawAction->setStatusTip(tr("Each redrawing of item gives a random color"));
    debugDrawAction->setCheckable(true);
    connect(debugDrawAction, SIGNAL(toggled(bool)), this, SLOT(debugDrawCahnged(bool)));

    // Menu-Help
    helpAction = new QAction(tr("Help"), this);
    helpAction->setShortcut(tr("F1"));
    helpAction->setStatusTip(tr("Offline help"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    docsAction = new QAction(tr("OpevCV docs"), this);
    docsAction->setStatusTip(tr("OpevCV online docs"));
    connect(docsAction, SIGNAL(triggered()), this, SLOT(docs()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setStatusTip(tr("About OpencvFilters"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

}

//------------------------------------------------------------------------
// Menu:
//
// -File
// ---New
// ---Open
// ---Save
// ---SaveAs
// ---Exit
// -Edit
// --Add
// ----...
// ---Delete
// -Help
// ---Help
// ---Docs
// ---About
//
//------------------------------------------------------------------------
void MainWindow::createMenus()
{
    // Menu-File
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(fileNewAction);
    fileMenu->addAction(fileOpenAction);
    fileMenu->addAction(fileSaveAction);
    fileMenu->addAction(fileSaveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Menu-Edit
    editMenu = menuBar()->addMenu(tr("Edit")); 
    // Create Add submenu and fill it with all addItemAction actions
    // or disable it if there is no filters
    addItemSubmenu = editMenu->addMenu(tr("Add"));
    addItemSubmenu->setDisabled(addItemActionVector.isEmpty());
    foreach(QAction * nextAction, addItemActionVector) {
        addItemSubmenu->addAction(nextAction);
    }
    editMenu->addAction(deleteItemAction);

    // Menu-Debug
    debugMenu = menuBar()->addMenu(tr("Debug"));
    debugMenu->addAction(debugDrawAction);

    // Menu-Help
    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(docsAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);

}



//------------------------------------------------------------------------
// Toolbars:
// File
// Edit
// Scene
// Debug
//------------------------------------------------------------------------
void MainWindow::createToolbars()
{
    // File toolbar
    fileToolbar = addToolBar(tr("File"));
    fileToolbar->addAction(fileNewAction);
    fileToolbar->addAction(fileOpenAction);
    fileToolbar->addAction(fileSaveAction);
    fileToolbar->addAction(fileSaveAsAction);

    // Debug Toolbar
    debugToolbar = addToolBar(tr("Debug"));
    debugToolbar->addAction(debugDrawAction);
}


//------------------------------------------------------------------------
// Toolbox:
// Add
//------------------------------------------------------------------------
void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),0, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
//! [21]

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    addButtonGroup = new QButtonGroup(this);
    connect(addButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QGridLayout *backgroundLayout = new QGridLayout;
    foreach(QAction * nextAction, addItemActionVector) {
        addItemSubmenu->addAction(nextAction);







        backgroundLayout->addWidget(createBackgroundCellWidget(tr("Blue Grid"), ":/images/background1.png"), 0, 0);
    }

    backgroundLayout->setRowStretch(2, 10);
    backgroundLayout->setColumnStretch(2, 10);

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);


    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));

}




//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void MainWindow::fileNew()
{
    //scene->clear();
    QMessageBox::about(this, tr("fileNew"), tr("fileNew"));
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void MainWindow::fileOpen()
{
    qDebug() << __FUNCTION__;

//    QString fileName = QFileDialog::getOpenFileName(this,
//     tr("Open Node Diagram"), "./", tr("Diagram Files (*.diagram)"));

//    QFile f(fileName);
//    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;

//    //clear old scene
//    scene->clear();
//    /*//this gives problems with connections, which are deleted by nodes!
//    QList<QGraphicsItem *> list = scene->items();
//    QList<QGraphicsItem *>::Iterator it = list.begin();
//    for ( ; it != list.end(); ++it )
//    {
//        QGraphicsItem* gi = (*it);
//        if ( (*it) && (*it)->parentItem() == 0 && (*it)->type() == NodeItem::Type)
//            {
//                    //NodeItem* node = static_cast<NodeItem*>(*it)
//                    scene->removeItem(*it);
//                    delete *it;
//            }
//    }
//    */

//    QTextStream in(&f);
//    QMap<int, ExampleBaseNode*> map ;

//    while (!in.atEnd()) {
//        QString l = in.readLine();
//        int type = l.split("=")[1].toInt();
//        ExampleBaseNode* n = scene->createNode(type);
//        n->deserialize(in, map);
//    }
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void MainWindow::fileSave()
{
    qDebug() << __FUNCTION__;

/*

    QString fileName = QFileDialog::getSaveFileName(this,
     tr("Save Node Diagram"), "./", tr("Diagram Files (*.diagram)"));

    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);

    foreach( QGraphicsItem* i, scene->items()) {
        //if (i->inherits("ExampleBaseNode")) {
        if (i->type() == NodeItem::Type) {
            ExampleBaseNode* n = static_cast<ExampleBaseNode*>(i);
            n->serialize(out);
        }
    }
*/
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
void MainWindow::fileSaveAs()
{
    qDebug() << __FUNCTION__;

/*
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Node Diagram"), "./", tr("Diagram Files (*.diagram)"));
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&f);

    foreach( QGraphicsItem* i, scene->items()) {
        if (i->type() == NodeItem::Type) {
            ExampleBaseNode* n = static_cast<ExampleBaseNode*>(i);
            n->serialize(out);
        }
    }
*/
}

//------------------------------------------------------------------------
// Menu-Edit-Add
//------------------------------------------------------------------------
void MainWindow::addItem()
{
    qDebug() << __FUNCTION__;

    // Get parent action
    QAction *action = qobject_cast< QAction* >(QObject::sender());

    // Add test item
    if (action->data().toString() == "000") {
        QGraphicsRectItem * newItem = new QGraphicsRectItem(100, 100, 100, 100);
        newItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        newItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        newItem->setFlag(QGraphicsItem::ItemIsFocusable, true);
        nodeEditorScene->addItem(newItem);

        // Transparent Slider
        QSlider * theSlider = new QSlider();
        theSlider->setStyleSheet("background-color:transparent");
        nodeEditorScene->addWidget(theSlider);

        // Another test item
        //    // Create Node and add into the Scene
        //    QWidget* newWidget = new TestWidget_1();
        //    NodeItem * newItem = new NodeItem(newWidget);
        //    nodeEditorScene->addItem(newItem);
        //    // Add ports
        //    QPushButton * newBtn = new QPushButton("port in");
        //    NodePort * newPortIn = new NodePort(newItem, nodeEditorScene, newBtn, NodePort::In, NodePort::Left);
        //    QLabel * newLbl = new QLabel("port out");
        //    NodePort * newPortOut = new NodePort(newItem, nodeEditorScene, newLbl, NodePort::Out, NodePort::Right);
        //    newItem->addPort(newPortIn);
        //    newItem->addPort(newPortOut);

        return;
    }



    // Extract user data from action and create filter
    try {
        LibFilter::CreateFilterResult result = libFilter.createFilter(action->data().toString());

        // Create Node and add into the Scene
        NodeItem * newItem = new NodeItem(result.widget);
        nodeEditorScene->addItem(newItem);
        // Add ports
        NodePort * newPortIn = new NodePort(newItem, NodePort::In, NodePort::Left);
        NodePort * newPortOut = new NodePort(newItem, NodePort::Out, NodePort::Right);
        newItem->addPort(newPortIn);
        newItem->addPort(newPortOut);

    } catch (std::runtime_error& e) {
        QMessageBox::critical(this, tr("Error"), e.what());
    }
}

//------------------------------------------------------------------------
// Menu-Edit-Delete
//------------------------------------------------------------------------
void MainWindow::deleteItem()
{
    qDebug() << __FUNCTION__;

    nodeEditorScene->deleteSelectedItems();
}


//------------------------------------------------------------------------
// Menu-View-Scale
//------------------------------------------------------------------------
void MainWindow::scaleCahnged()
{

}

//------------------------------------------------------------------------
// Menu-Debug-Debugdraw
//------------------------------------------------------------------------
void MainWindow::debugDrawCahnged(bool checked)
{

}


//------------------------------------------------------------------------
// Menu-Help-Help
//------------------------------------------------------------------------
void MainWindow::help()
{
    QMessageBox::about(this, tr("Help OpencvFilters"),
                       tr("Help OpencvFilters"));
}

//------------------------------------------------------------------------
// Menu-Help-Docs
//------------------------------------------------------------------------
void MainWindow::docs()
{
    QDesktopServices::openUrl(QUrl("http://docs.opencv.org/3.0.0/"));
}

//------------------------------------------------------------------------
// Menu-Help-About
//------------------------------------------------------------------------
void MainWindow::about()
{
    QMessageBox::about(this, tr("About OpencvFilters"),
                       tr("About OpencvFilters"));
}




