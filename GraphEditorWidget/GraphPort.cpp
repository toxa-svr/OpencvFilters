#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"

GraphPort::GraphPort(QGraphicsItem *parent):
    QGraphicsPathItem(parent),
    radius_(PORT_RADIUS_DEFAULT),
    margin_(2),
    portFlags_(0)
{
    label_ = new QGraphicsTextItem(this);

	QPainterPath p;
	p.addEllipse(-radius_, -radius_, 2*radius_, 2*radius_);
	setPath(p);

	setPen(QPen(Qt::darkRed));
	setBrush(Qt::red);
}


GraphPort::~GraphPort()
{
    foreach(GraphConnection *conn, connections_) {
		delete conn;
    }
}


void GraphPort::setIsOutput(bool o)
{
	isOutput_ = o;

	QFontMetrics fm(scene()->font());
    QRect r = fm.boundingRect(name_);

	if (isOutput_)
        label_->setPos(-radius_ - margin_ - label_->boundingRect().width(), -label_->boundingRect().height()/2);
	else
        label_->setPos(radius_ + margin_, -label_->boundingRect().height()/2);
}


void GraphPort::setFlags(int f)
{
    portFlags_ = f;

    if (portFlags_ & TypePort) {
		QFont font(scene()->font());
		font.setItalic(true);
        label_->setFont(font);
		setPath(QPainterPath());
    }
    else if (portFlags_ & NamePort) {
		QFont font(scene()->font());
		font.setBold(true);
        label_->setFont(font);
		setPath(QPainterPath());
    }
}


bool GraphPort::isConnectedWith(GraphPort *other) const
{
    foreach(GraphConnection *conn, connections_) {
        if (conn->port1() == other || conn->port2() == other) {
			return true;
        }
    }
	return false;
}


QVariant GraphPort::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged) {
        foreach(GraphConnection *conn, connections_) {
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}
