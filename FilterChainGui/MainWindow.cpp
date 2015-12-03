#include <QDesktopServices>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    createToolbars();
    //createToolBox();

    //TODO ugly
    scene = new ExampleDiagramScene(itemMenu);
    scene->mItemMenu = itemMenu;


    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(nodeItemInserted(NodeItem *)), this, SLOT(itemInserted(NodeItem *)));
    //connect(scene, SIGNAL(itemSelected(QGraphicsItem *)),
    //    this, SLOT(itemSelected(QGraphicsItem *)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);


    view = new QGraphicsView(scene);
    //view = new MyFasterGraphicView(scene);
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("NodeEditorScene"));


}

MainWindow::~MainWindow()
{
    delete ui;
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
    // Create actions for all available filters
    // TODO
    addItemActionVector.clear();
    for (int i = 0; i < 3; i++) {
        QAction * newAddAction = new QAction(tr("Filter ") + QString::number(i), this);
        newAddAction->setStatusTip(tr("Add new filter ") + QString::number(i));
        connect(newAddAction, SIGNAL(triggered()), this, SLOT(addItem()));
        // Add user data to action
        //newAddAction->setData();
        addItemActionVector.append(newAddAction);
    }

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
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Menu-Edit
    editMenu = menuBar()->addMenu(tr("Edit"));
    // Fill submenu with all addItemAction actions
    addItemSubmenu = editMenu->addMenu(tr("Add"));
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
    QMessageBox::about(this, tr("fileOpen"), tr("fileOpen"));

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
    QMessageBox::about(this, tr("fileSave"), tr("fileSave"));
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
    QMessageBox::about(this, tr("fileSaveAs"), tr("fileSaveAs"));
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
    // Get parent action
    QAction *action = qobject_cast< QAction* >(QObject::sender());
    QMessageBox::about(this, tr("Add"), action->text());

    // Extract user data from action and create filter
    //action->data()
}

//------------------------------------------------------------------------
// Menu-Edit-Delete
//------------------------------------------------------------------------
void MainWindow::deleteItem()
{
//	if (scene->selectedItems().count()) {
//		foreach (QGraphicsItem *item, scene->selectedItems()) {
//			/*//now in dtor:
//			if (item->type() == DiagramItem::Type) {
//				qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
//			}

//			//dw isn't it better to delete stuff in destructors??
//			if (item->type() == NodeItem::Type) {
//				qgraphicsitem_cast<NodeItem *>(item)->removeConnections();
//			}
//			*/

//			//dw we are doing that now in removeConnections from idem dtor, is that good idea?
//			//scene->removeItem(item);

//			//can we delete all item or better only ours, and why is it not deleted automatically on removal? what is the correct way?
//			delete item;
//		}
//		scene->clearSelection();
//		scene->clearFocus();
//	}
//	//maybe we are embedding a window so handle this too (TODO: is there a better way?)
//	else if (this->scene->focusItem() && this->scene->focusItem()->type() == NodeItem::Type) {
//        NodeItem* item = qgraphicsitem_cast<NodeItem *>(this->scene->focusItem());
//		//now in dtor: item->removeConnections();

//		//dw we are doing that now in removeConnections from idem dtor, is that good idea?
//		//scene->removeItem(item);
//		delete item;
//		scene->clearSelection();
//		scene->clearFocus();
//    }
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




