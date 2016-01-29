#pragma once

#include <QtWidgets>

class NodeItem;
class NodeConnection;



class NodePort : public QGraphicsItem
{
public:
	enum { Type = UserType + 666 + 6 };
    int type() const { return Type;}

    enum PortType { In=1, Out=2, InOut=3 };
    PortType connectorType() const { return mConnectorType; }
    void setConnectorType(PortType c) {mConnectorType = c;	}
    enum PortAlignment { None=0, Left=1, Right=2, Bottom=3, Top=4 };
    PortAlignment connectorAlignment() const {	return mConnectorAlignment;	}
    void setConnectorAlignment(PortAlignment alignment) {mConnectorAlignment = alignment;}
	bool singleConnection() const { return mSingleConnection; }
    void setSingleConnection(bool singleConnection) {mSingleConnection = singleConnection;	}
	bool selfConnections() const { return mSelfConnections; }
    void setSelfConnections(bool selfConnections) {	mSelfConnections = selfConnections;	}


    NodePort(NodeItem *parent, QGraphicsScene *scene, /*QLabel*/QWidget* widget, PortType  con = In, const PortAlignment connectorAlignment = PortAlignment::Left, const bool singleConnection = false, const bool disableWidgetOnConnection = false, const int radius = 7, const bool selfConnections = false);
    virtual ~NodePort();



    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	//dw
	void updatePosition();
    void addConnection(NodeConnection *connection);
    void deleteConnection(NodeConnection *connection);
	void deleteConnections();
    void removeConnection(NodeConnection *connection);

	void setHighlight(bool highlight);

//private:
	int mRadius;
    PortType mConnectorType;
	NodeItem *parent;
	QWidget* mWidget;
    PortAlignment mConnectorAlignment;
    QList<NodeConnection*> connections;
	QColor darkColor;
	bool highlight;
	bool mSingleConnection;
	bool mSelfConnections;
	bool mDisableWidgetOnConnection;

	//ugly, but node ctor is called after wiget is removed, but delete of connector would otherwise activate label widget
    void removeWidget();

	void update(const QRectF & rect = QRectF());

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	void debugPaint(QPainter *painter);

};

