#include <QtGui>
#include <QtWidgets>
#include <QGraphicsSceneEvent>
#include <QDebug>

#include "../inc/NodeEditorWidget.h"
#include "NodeItem.h"
#include "NodeConnection.h"
#include "NodePort.h"



NodeEditorWidget::NodeEditorWidget(QWidget* parent) :
    QGraphicsView(parent)
{
    qDebug() << __FUNCTION__;

    // QGraphicsView settings
    setRenderHint(QPainter::Antialiasing, true);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}


/*
QGraphicsItem * NodeEditorWidget::addNode()
{
    NodeItem *newNode = createGraphNode();
    return newNode;
}

QGraphicsItem * NodeEditorWidget::addNode(const QWidget &widget)
{
    NodeItem *newNode = createGraphNode();
//    newNode->setWidget(&widget);
    return newNode;
}

QGraphicsItem * NodeEditorWidget::addNode(const QString &title, const QString &smallTitle, const QPixmap &icon, const QWidget &widget, const bool isCollapsed)
{
    NodeItem *newNode = createGraphNode();
//    newNode->setTitle(title);
//    newNode->setSmallTitle(smallTitle);
//    newNode->setIcon(&icon);
//    newNode->setWidget(&widget);
//    newNode->setCollpsed(isCollapsed);
    return newNode;
}

QGraphicsItem * NodeEditorWidget::createGraphNode()
{
    NodeItem *newNode = new NodeItem(0);
//    scene.addItem(newNode);
//    newNode->setPos(this->sceneRect().center().toPoint());

//    QPushButton *btn = new QPushButton("test");
//    scene.addWidget(btn, Qt::Tool);



//    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF());
//    rectItem->setPen(QPen(Qt::black));
//    rectItem->setBrush(QBrush(Qt::green));
//    rectItem->setRect(QRectF(-30, -30, 120, 80));
//    rectItem->setFlags(QGraphicsItem::ItemIsMovable);


//    QGraphicsTextItem* textItem = scene.addText("Move us with your mouse");
//    textItem->setDefaultTextColor(Qt::red);
//    textItem->setFlags(QGraphicsItem::ItemIsMovable);

//    QPushButton* button = new QPushButton("Ok");
//    QGraphicsProxyWidget* widgetItem = scene.addWidget(button);
//    widgetItem->setPos(0, 0);
//    widgetItem->setFlags(QGraphicsItem::ItemIsMovable);
//    widgetItem->setParentItem(rectItem);

//    QLabel* lbl = new QLabel("Label");
//    QGraphicsProxyWidget* labelItem = scene.addWidget(lbl);
//    labelItem->setPos(30, 30);
//    labelItem->setFlag(QGraphicsItem::ItemIsMovable, true);
//    labelItem->setParentItem(rectItem);


    return newNode;
}


QGraphicsItem * NodeEditorWidget::addPort()
{
//    //addPort("port", true, 0, 0);
//    //addPort("port1", false, 0, 0);
    return nullptr;
}


QGraphicsItem * NodeEditorWidget::addConnection()
{
    return nullptr;
}

*/



//void NodeEditorWidget::editorLostFocus(DiagramTextItem *item)
//{
//    QTextCursor cursor = item->textCursor();
//    cursor.clearSelection();
//    item->setTextCursor(cursor);
//    if (item->toPlainText().isEmpty()) {
//        removeItem(item);
//        item->deleteLater();
//    }
//}
//void setItemType(DiagramItem::DiagramType type)
//{
//    mItemType = type;
//}


