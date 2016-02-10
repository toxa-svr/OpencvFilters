////main.cpp
//#include <QApplication>
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QGraphicsEllipseItem>
//#include <QGraphicsRectItem>
//#include <QMouseEvent>
//#include <QPointer>

//class Notifier : public QObject
//{
//   Q_OBJECT
//   int m_count;
//public:
//   Notifier() : m_count(0) {}
//   int count() const { return m_count; }
//   void inc() { m_count ++; }
//   void notify() { m_count = 0; emit notification(); }
//   Q_SIGNAL void notification();
//};

//typedef QPointer<Notifier> NotifierPointer;
//Q_DECLARE_METATYPE(NotifierPointer)

//template <typename T> class NotifyingItem : public T
//{
//protected:
//   QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
//      QVariant v;
//      if (change == T::ItemPositionHasChanged && this->scene() &&
//          (v=this->scene()->property("notifier")).isValid())
//      {
//         NotifierPointer notifier = v.value<NotifierPointer>();
//         notifier->inc();
//         if (notifier->count() >= this->scene()->selectedItems().count()) {
//            notifier->notify();
//         }
//      }
//      return T::itemChange(change, value);
//   }
//};

////
//// Note that all you need to make Circle a notifying item is to derive from
//// NotifyingItem<basetype>.

//class Circle : public NotifyingItem<QGraphicsEllipseItem>
//{
//   QBrush brush;
//public:
//   Circle(const QPointF & c) : brush("lightgray") {
//      const qreal r = 10.0 + (50.0*qrand())/RAND_MAX;
//      setRect(QRectF(-r, -r, 2.0*r, 2.0*r));
//      setPos(c);
//      setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
//               QGraphicsItem::ItemSendsGeometryChanges);
//      setPen(QPen("red"));
//      setBrush(brush);
//   }

//};

//class View : public QGraphicsView
//{
//   Q_OBJECT
//   QGraphicsScene scene;
//   Notifier notifier;
//   QGraphicsSimpleTextItem * text;
//   QGraphicsRectItem * centroid;
//   int deltaCounter;
//public:
//   explicit View(QWidget *parent = 0);
//   ~View() {
//      scene.disconnect(this);
//      // Otherwise gotUpdates will try to access the destroyed centroid while the scene's
//      // destructor is running and the children, inluding the centroid, are already dead.
//   }
//protected:
//   Q_SLOT void gotUpdates();
//   void mousePressEvent(QMouseEvent *event);
//};

//View::View(QWidget *parent) :
//   QGraphicsView(parent),
//   text(new QGraphicsSimpleTextItem()),
//   centroid(new QGraphicsRectItem(-5, -5, 10, 10)),
//   deltaCounter(0)
//{
//   centroid->hide();
//   centroid->setRotation(45.0);
//   centroid->setPen(QPen("blue"));
//   centroid->setZValue(2);
//   scene.addItem(centroid);
//   text->setPos(5, 470);
//   text->setZValue(1);
//   scene.addItem(text);
//   setRenderHint(QPainter::Antialiasing);
//   setScene(&scene);
//   setSceneRect(0,0,500,500);
//   scene.setProperty("notifier", QVariant::fromValue(NotifierPointer(&notifier)));
//   connect(&notifier, SIGNAL(notification()), SLOT(gotUpdates()));
//   connect(&scene, SIGNAL(selectionChanged()), SLOT(gotUpdates()));
//}

//void View::gotUpdates()
//{
//   if (scene.selectedItems().isEmpty()) {
//      this->centroid->hide();
//      return;
//   }
//   this->centroid->show();
//   QPointF centroid(0.0, 0.0);
//   qreal area = 0.0;
//   foreach (QGraphicsItem * item, scene.selectedItems()) {
//      const QRectF r = item->boundingRect();
//      const qreal a = r.width() * r.height();
//      centroid += item->pos() * a;
//      area += a;
//   }
//   centroid /= area;
//   QString st = QString("delta #%1 with %2 items, centroid at %3, %4")
//         .arg(deltaCounter++).arg(scene.selectedItems().count())
//         .arg(centroid.x(), 0, 'f', 1).arg(centroid.y(), 0, 'f', 1);
//   this->centroid->setPos(centroid);
//   text->setText(st);
//}

//void View::mousePressEvent(QMouseEvent *event)
//{
//   const QPointF center = mapToScene(event->pos());
//   if (! scene.itemAt(center, QTransform())) scene.addItem(new Circle(center));
//   QGraphicsView::mousePressEvent(event);
//}

//int main(int argc, char *argv[])
//{
//   QApplication a(argc, argv);
//   View v;
//   v.show();
//   return a.exec();
//}
//#include "mainwindow.moc"






#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NodeEditorScene.h"
#include "NodeEditorWidget.h"
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

    //newItem->addPort(newPortIn);
    //newItem->addPort(newPortOut);
}

void MainWindow::on_pushButton_2_clicked()
{
    QGraphicsRectItem * newItem = new QGraphicsRectItem(100, 100, 100, 100);
    newItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    newItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    newItem->setFlag(QGraphicsItem::ItemIsFocusable, true);
    nodeEditorScene->addItem(newItem);
}

void MainWindow::on_delButton_clicked()
{
    nodeEditorScene->deleteSelectedItems();
}
