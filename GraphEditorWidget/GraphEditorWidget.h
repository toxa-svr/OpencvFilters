#ifndef GRAPHEDITORWIDGET_H
#define GRAPHEDITORWIDGET_H

#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"


//-------------------------------------------------
// Settings for Widget
//-------------------------------------------------
class GraphEditorSettings
{
    // Node representation
    bool showNodeTitle;
    bool showNodeSmallTitle;
    bool showNodeIcon;
    bool showNodeWidget;
    bool showNodePortNames;

    // Port representation

    // Connection representation
};




class GraphEditorWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphEditorWidget (QWidget* parent = nullptr);

    QGraphicsItem * addNode();
    QGraphicsItem * addNode(const QWidget &widget);
    QGraphicsItem * addNode(const QString &title, const QString &smallTitle, const QPixmap &icon, const QWidget &widget, const bool isCollapsed);



    QGraphicsItem * addPort();
    QGraphicsItem * addConnection();


    //QGraphicsItem * addPort(QGraphicsItem * node, );
    //QGraphicsItem * addConnection();

    //void save(QDataStream &ds);
    //void load(QDataStream &ds);

    QGraphicsItem *itemAt(const QPointF&);


protected:
    bool eventFilter(QObject *, QEvent *);


private:
    QGraphicsScene scene;
    GraphConnection *conn;
    GraphEditorSettings settings;
    //GraphNode *selBlock;


    GraphNode * createGraphNode();
};

#endif // GRAPHEDITORWIDGET_H

