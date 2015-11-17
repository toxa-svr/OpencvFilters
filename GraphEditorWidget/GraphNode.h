#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsPathItem>

class GraphPort;

class GraphNode : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 3 };

    GraphNode(QGraphicsItem *parent = 0);

    GraphPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
    void addInputPort(const QString &name)        { addPort(name, false); }
    void addOutputPort(const QString &name)       { addPort(name, true); }
    void addInputPorts(const QStringList &names)  { foreach(QString n, names) addPort(n, false); }
    void addOutputPorts(const QStringList &names) { foreach(QString n, names) addPort(n, true); }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVector<GraphPort*> ports();

	int type() const { return Type; }

    //void save(QDataStream&);
    //void load(QDataStream&, QMap<quint64, GraphEditorPort*> &portMap);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	int horzMargin;
	int vertMargin;
	int width;
	int height;
};

#endif // GRAPHNODE_H


