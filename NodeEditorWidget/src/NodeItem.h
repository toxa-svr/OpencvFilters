#pragma once

#include <QtWidgets>
#include "NodeEditorWidget.h"
#include "NodeConnection.h"
#include "NodePort.h"

class NodePort;
class NodeConnection;



//! [0]
class NodeItem : public QGraphicsProxyWidget
{
	Q_OBJECT
public:
    enum { Type = UserType + 666 + 1 };
	int type() const
        { return Type;}

    NodeItem(QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0, Qt::WindowFlags wFlags = 0);
	virtual ~NodeItem();
    void deleteConnections();

    void addConnector(NodePort* nc);


	//dw
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void setWidget(QWidget *widget);

	QRectF boundingRect() const;
	QPainterPath shape() const;

	//void update(const QRectF & rect = QRectF());

    QList<NodePort *> connectors;

	public slots:
		void deleted();
		void deleted(int result);

		//dw try overriding QWidget slot
		void hide();

/*
void 	accepted ()
void 	finished ( int result )
void 	rejected ()
*/

//dw666 orig:	QList<NodeConnector *> connectors;

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

	bool shouldMoveNode(QGraphicsSceneMouseEvent *mouseEvent);
	//const static QStringList shouldNotMoveTypes << "foo" << "bar";
	//const static char* shouldNotMoveTypes = {};
	const static char* shouldMoveOnClickTypes[];


	void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );


	bool mControlResizeHandles;
	bool mNoResize;

	//dw 669: new
	void resizeEvent ( QGraphicsSceneResizeEvent * event );


private:
    QMenu *mContextMenu;



	void updateConnectorsPos();

	bool isMoving;

	void removeWigetFromConnectors();

	void debugPaint(QPainter *painter);

	int mMaxRadius;


};

