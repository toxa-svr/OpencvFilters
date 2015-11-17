#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"


GraphConnection::GraphConnection(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	setPen(QPen(Qt::black, 2));
	setBrush(Qt::NoBrush);
	setZValue(-1);
    port1_ = 0;
    port2_ = 0;
}


GraphConnection::~GraphConnection()
{
    if (port1_) port1_->removeConnection(this);
    if (port2_) port2_->removeConnection(this);
}


void GraphConnection::updatePath()
{
	QPainterPath p;

	//QPointF pos1(m_port1->scenePos());
	//QPointF pos2(m_port2->scenePos());

    p.moveTo(pos1_);

    qreal dx = pos2_.x() - pos1_.x();
    qreal dy = pos2_.y() - pos1_.y();

    QPointF ctr1(pos1_.x() + dx * 0.25, pos1_.y() + dy * 0.1);
    QPointF ctr2(pos1_.x() + dx * 0.75, pos1_.y() + dy * 0.9);

    p.cubicTo(ctr1, ctr2, pos2_);

	setPath(p);
}


/*
void GraphEditorConnection::save(QDataStream &ds)
{
	ds << (quint64) m_port1;
	ds << (quint64) m_port2;
}

void GraphEditorConnection::load(QDataStream &ds, const QMap<quint64, GraphEditorPort*> &portMap)
{
	quint64 ptr1;
	quint64 ptr2;
	ds >> ptr1;
	ds >> ptr2;

	setPort1(portMap[ptr1]);
	setPort2(portMap[ptr2]);
	updatePosFromPorts();
	updatePath();
}
*/
