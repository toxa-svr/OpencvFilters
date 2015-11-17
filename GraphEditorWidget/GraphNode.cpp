#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"


GraphNode::GraphNode(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	QPainterPath p;
	p.addRoundedRect(-50, -15, 100, 30, 5, 5);
	setPath(p);
	setPen(QPen(Qt::darkGreen));
	setBrush(Qt::green);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	horzMargin = 20;
	vertMargin = 5;
	width = horzMargin;
	height = vertMargin;
}


GraphPort* GraphNode::addPort(const QString &name, bool isOutput, int flags, int ptr)
{
    GraphPort *port = new GraphPort(this);
	port->setName(name);
	port->setIsOutput(isOutput);
    port->setNode(this);
    port->setFlags(flags);
	port->setPtr(ptr);

	QFontMetrics fm(scene()->font());
	int w = fm.width(name);
	int h = fm.height();
	// port->setPos(0, height + h/2);
	if (w > width - horzMargin)
		width = w + horzMargin;
	height += h;

	QPainterPath p;
	p.addRoundedRect(-width/2, -height/2, width, height, 5, 5);
	setPath(p);

	int y = -height / 2 + vertMargin + port->radius();
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() != GraphPort::Type)
			continue;

        GraphPort *port = (GraphPort*) port_;
		if (port->isOutput())
			port->setPos(width/2 + port->radius(), y);
		else
			port->setPos(-width/2 - port->radius(), y);
		y += h;
	}

	return port;
}


QVector<GraphPort*> GraphNode::ports()
{
    QVector<GraphPort*> res;
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() == GraphPort::Type) {
            res.append((GraphPort*) port_);
        }
    }
    return res;
}


void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	if (isSelected()) {
		painter->setPen(QPen(Qt::darkYellow));
		painter->setBrush(Qt::yellow);
	} else {
		painter->setPen(QPen(Qt::darkGreen));
		painter->setBrush(Qt::green);
	}

	painter->drawPath(path());
}


QVariant GraphNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    Q_UNUSED(change);
	return value;
}


/*
void GraphNode::save(QDataStream &ds)
{
    ds << pos();

    int count(0);

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != GraphEditorPort::Type)
            continue;

        count++;
    }

    ds << count;

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() != GraphEditorPort::Type)
            continue;

        GraphEditorPort *port = (GraphEditorPort*) port_;
        ds << (quint64) port;
        ds << port->name();
        ds << port->isOutput();
        ds << port->portFlags();
    }
}


void GraphNode::load(QDataStream &ds, QMap<quint64, GraphEditorPort*> &portMap)
{
    QPointF p;
    ds >> p;
    setPos(p);
    int count;
    ds >> count;
    for (int i = 0; i < count; i++)
    {
        QString name;
        bool output;
        int flags;
        quint64 ptr;

        ds >> ptr;
        ds >> name;
        ds >> output;
        ds >> flags;
        portMap[ptr] = addPort(name, output, flags, ptr);
    }
}
*/
