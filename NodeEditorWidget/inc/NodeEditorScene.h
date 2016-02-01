#pragma once

#include <QtWidgets>

#include "NodeItem.h"
#include "NodePort.h"
#include "NodeConnection.h"


class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NodeEditorScene(QWidget *parent = nullptr);
    NodeItem* createNode();


signals:
    void nodeItemInserted(NodeItem *item);
    void nodeInserted(QGraphicsItem *item);
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




