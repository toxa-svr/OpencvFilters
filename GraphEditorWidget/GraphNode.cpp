#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>
#include <QtWidgets>
#include <QStyleOptionGraphicsItem>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"


GraphNode::GraphNode(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
    initNodeWidget();
}

//GraphNode::GraphNode(QGraphicsItem *parent, const QWidget &widget) : QGraphicsPathItem(parent)
//{
//    setWidget(widget);
//    initNodeWidget();
//}

//GraphNode::GraphNode(QGraphicsItem *parent, const QString &title, const QString &smallTitle, const QPixmap *icon, const QWidget *widget, const bool isCollapsed) : QGraphicsPathItem(parent)
//{
//    settings.title = title;
//    settings.smallTitle = smallTitle;
//    settings.icon = icon;
//    settings.widget = widget;
//    settings.isCollapsed = isCollapsed;
//    initNodeWidget();
//}

//GraphNode::GraphNode(QGraphicsItem *parent, const GraphNodeSettings &settings_) : QGraphicsPathItem(parent)
//{
//    settings = settings_;
//    initNodeWidget();
//}





//-------------------------------------------------
// Create GraphicsItem for a new GraphNode
//-------------------------------------------------
void GraphNode::initNodeWidget ()
{
//    QPainterPath p;
//    p.addRoundedRect(-50, -15, 100, 30, 5, 5);
//    setPath(p);
//    setPen(QPen(Qt::darkGreen));
//    setBrush(Qt::green);
//    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemIsSelectable);

    horzMargin_ = 20;
    vertMargin_ = 5;
    width_ = horzMargin_;
    height_ = vertMargin_;
}


//-------------------------------------------------
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
    if (w > width_ - horzMargin_)
        width_ = w + horzMargin_;
    height_ += h;

	QPainterPath p;
    p.addRoundedRect(-width_/2, -height_/2, width_, height_, 5, 5);
	setPath(p);

    int y = -height_ / 2 + vertMargin_ + port->radius();
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() != GraphPort::Type)
			continue;

        GraphPort *port = (GraphPort*) port_;
		if (port->isOutput())
            port->setPos(width_/2 + port->radius(), y);
		else
            port->setPos(-width_/2 - port->radius(), y);
		y += h;
	}

	return port;
}

//-------------------------------------------------
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

//-------------------------------------------------
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


//-------------------------------------------------
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
