#pragma once

#include <QtWidgets>

class NodeItem;
class NodeConnection;
class NodePort;



//-------------------------------------------------
// Settings for whole Widget
//-------------------------------------------------
struct NodeEditorSettings
{
    // Widget representation
    bool debugDraw;

    // Node representation
    bool showNodeTitle;
    bool showNodeSmallTitle;
    bool showNodeIcon;
    bool showNodeWidget;
    bool showNodePortNames;

    // Port representation

    // Connection representation
    QColor connectionLineColor;
};








class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NodeEditorScene(QWidget *parent = nullptr);


    QGraphicsItem * addNode();
    QGraphicsItem * addNode(const QWidget &widget);
    QGraphicsItem * addNode(const QString &title, const QString &smallTitle, const QPixmap &icon, const QWidget &widget, const bool isCollapsed);
    QGraphicsItem * addPort();
    QGraphicsItem * addConnection();
    //QGraphicsItem *itemAt(const QPointF&);
    //void save(QDataStream &ds);
    //void load(QDataStream &ds);

    // TODO hide
    NodeEditorSettings settings;

signals:
    //void itemInserted(DiagramItem *item);
    //void textInserted(QGraphicsTextItem *item);
	void nodeInserted(QGraphicsItem *item);
	void nodeItemInserted(NodeItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);



private:
    bool isItemChange(int type);
    bool leftButtonDown;
    QPointF startPoint;
    NodeConnection* tmpConnection;
    NodePort* tmpPort;
    NodePort* existingPort;
    NodePort* lastHighlighted;



    NodeConnection *conn;
    NodeItem * createGraphNode();
};







class NodeEditorWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit NodeEditorWidget (QWidget* parent = nullptr);

private:
    NodeEditorScene* scene;

};

