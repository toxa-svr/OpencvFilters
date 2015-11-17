#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>


#include "GraphEditorWidget.h"
#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"




GraphEditorWidget::GraphEditorWidget(QWidget* parent) :
    QGraphicsView(parent),
    conn(nullptr)
{

    this->setScene(&scene); // set QGraphicsScene for this QGraphicsView
    this->setRenderHint(QPainter::Antialiasing, true);

    scene.installEventFilter(this); // add event filter for QGraphicsScene to handle events here

/*
    GraphNode *b = new GraphNode(0);
    scene->addItem(b);
    b->addPort("test", 0, GraphEditorPort::NamePort);
    b->addPort("TestBlock", 0, GraphEditorPort::TypePort);
    b->addInputPort("in1");
    b->addInputPort("in2");
    b->addInputPort("in3");
    b->addOutputPort("out1");
    b->addOutputPort("out2");
    b->addOutputPort("out3");

    b = b->clone();
    b->setPos(150, 0);

    b = b->clone();
    b->setPos(150, 150);
*/

}

QGraphicsItem* GraphEditorWidget::itemAt(const QPointF &pos)
{
    QList<QGraphicsItem*> items = scene.items(QRectF(pos - QPointF(1,1), QSize(3,3)));

    foreach(QGraphicsItem *item, items) {
        if (item->type() > QGraphicsItem::UserType) {
            return item;
        }
    }
    return 0;
}

bool GraphEditorWidget::eventFilter(QObject *o, QEvent *e)
{
    QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

    switch ((int)e->type()) {
        case QEvent::GraphicsSceneMousePress:

            if ((int) me->button() == Qt::LeftButton) {
                QGraphicsItem *item = itemAt(me->scenePos());
                if (item && item->type() == GraphPort::Type) {
                    conn = new GraphConnection(0);
                    scene.addItem(conn);
                    conn->setPort1((GraphPort*) item);
                    conn->setPos1(item->scenePos());
                    conn->setPos2(me->scenePos());
                    conn->updatePath();
                    return true;
                }
                else if (item && item->type() == GraphNode::Type) {
                    /* if (selBlock)
                        selBlock->setSelected(); */
                    // selBlock = (QNEBlock*) item;
                }
            }
            else if ((int) me->button() == Qt::RightButton) {
                QGraphicsItem *item = itemAt(me->scenePos());
                if (item && (item->type() == GraphConnection::Type || item->type() == GraphNode::Type)) {
                    delete item;
                }
                //if (selBlock == (GraphNode*) item) {
                //    selBlock = 0;
                //}
            }
            break;

        case QEvent::GraphicsSceneMouseMove:
            if (conn) {
                conn->setPos2(me->scenePos());
                conn->updatePath();
                return true;
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            if (conn && me->button() == Qt::LeftButton) {
                QGraphicsItem *item = itemAt(me->scenePos());
                if (item && item->type() == GraphPort::Type) {
                    GraphPort *port1 = conn->port1();
                    GraphPort *port2 = (GraphPort*) item;

                    if (port1->getNode() != port2->getNode() &&
                        port1->isOutput() != port2->isOutput() &&
                        !port1->isConnectedWith(port2))
                    {
                        conn->setPos2(port2->scenePos());
                        conn->setPort2(port2);
                        conn->updatePath();
                        conn = 0;
                        return true;
                    }
                }

                delete conn;
                conn = 0;
                return true;
            }
            break;
    }

    return QObject::eventFilter(o, e);
}

/*
void GraphEditorWidget::save(QDataStream &ds)
{
    foreach(QGraphicsItem *item, scene->items())
        if (item->type() == GraphNode::Type)
        {
            ds << item->type();
            ((GraphNode*) item)->save(ds);
        }

    foreach(QGraphicsItem *item, scene->items())
        if (item->type() == GraphEditorConnection::Type)
        {
            ds << item->type();
            ((GraphEditorConnection*) item)->save(ds);
        }
}

void GraphEditorWidget::load(QDataStream &ds)
{
    scene->clear();

    QMap<quint64, GraphEditorPort*> portMap;

    while (!ds.atEnd())
    {
        int type;
        ds >> type;
        if (type == GraphNode::Type)
        {
            GraphNode *block = new GraphNode(0);
            scene->addItem(block);
            block->load(ds, portMap);
        } else if (type == GraphEditorConnection::Type)
        {
            GraphEditorConnection *conn = new GraphEditorConnection(0);
            scene->addItem(conn);
            conn->load(ds, portMap);
        }
    }
}
*/

void GraphEditorWidget::addNode()
{
    GraphNode *newNode = new GraphNode(0);

    scene.addItem(newNode);
    newNode->addPort("port", true, 0, 0);
    newNode->addPort("port1", false, 0, 0);
    newNode->setPos(this->sceneRect().center().toPoint());
}


void GraphEditorWidget::addConnection()
{

}




/*
QNEMainWindow::QNEMainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    scene = new QGraphicsScene();


    QAction *quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *loadAct = new QAction(tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Open a file"));
    connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    QAction *addAct = new QAction(tr("&Add"), this);
    addAct->setStatusTip(tr("Add a block"));
    connect(addAct, SIGNAL(triggered()), this, SLOT(addBlock()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    setWindowTitle(tr("Node Editor"));



    QDockWidget *dock = new QDockWidget(tr("Nodes"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    view = new QGraphicsView(dock);
    view->setScene(scene);

    view->setRenderHint(QPainter::Antialiasing, true);

    dock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, dock);








    nodesEditor = new QNodesEditor(this);
    nodesEditor->install(scene);


    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->addPort("test", 0, QNEPort::NamePort);
    b->addPort("TestBlock", 0, QNEPort::TypePort);
    b->addInputPort("in1");
    b->addInputPort("in2");
    b->addInputPort("in3");
    b->addOutputPort("out1");
    b->addOutputPort("out2");
    b->addOutputPort("out3");

    b = b->clone();
    b->setPos(150, 0);

    b = b->clone();
    b->setPos(150, 150);
}

QNEMainWindow::~QNEMainWindow()
{

}

void QNEMainWindow::addBlock()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
	static const char* names[] = {"Vin", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
	for (int i = 0; i < 4 + rand() % 3; i++)
	{
		b->addPort(names[rand() % 10], rand() % 2, 0, 0);
        b->setPos(view->sceneRect().center().toPoint());
	}
}

*/



