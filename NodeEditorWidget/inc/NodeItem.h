#pragma once

#include <QtWidgets>
#include <QList>

class NodePort;
class NodeConnection;


class NodeItem : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
    enum { Type = UserType + 666 + 1 };
    int type() const { return Type;}


    NodeItem(Qt::WindowFlags wFlags = 0, QGraphicsItem *parent = 0);
	virtual ~NodeItem();
    void deleteConnections();
    void addPort(NodePort* port);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QRectF boundingRect() const;
	QPainterPath shape() const;
    QList<NodePort *> ports;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isMoving;  // item is moving with mouse now (left button is pressed now)
    bool isMovable;
    bool isResizable;

    void updatePortsPos();
    void removeWigetFromPorts();
	void debugPaint(QPainter *painter);
};

