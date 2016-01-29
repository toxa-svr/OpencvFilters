#pragma once

#include <QtWidgets>

class NodePort;
class NodeConnection;



class NodeItem : public QGraphicsProxyWidget
{
	Q_OBJECT
public:
    enum { Type = UserType + 666 + 1 };
    int type() const { return Type;}

    NodeItem(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0, Qt::WindowFlags wFlags = 0);
	virtual ~NodeItem();
    void deleteConnections();
    void addPort(NodePort* nc);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setWidget(QWidget *widget);
	QRectF boundingRect() const;
	QPainterPath shape() const;
    QList<NodePort *> connectors;

public slots:
    void deleted();
    void deleted(int result);
    //dw try overriding QWidget slot
    void hide();

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	bool shouldMoveNode(QGraphicsSceneMouseEvent *mouseEvent);
	const static char* shouldMoveOnClickTypes[];
	void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
    void resizeEvent ( QGraphicsSceneResizeEvent * event );

	bool mControlResizeHandles;
	bool mNoResize;

private:
    QMenu *mContextMenu;
    bool isMoving;
    int mMaxRadius;

    void updatePortsPos();
    void removeWigetFromPorts();
	void debugPaint(QPainter *painter);
};

