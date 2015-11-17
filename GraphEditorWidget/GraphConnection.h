#ifndef GRAPHCONNECTION_H
#define GRAPHCONNECTION_H

#include <QGraphicsPathItem>

class GraphPort;

class GraphConnection : public QGraphicsPathItem
{
public:

    // Enable the use of qgraphicsitem_cast with this item.
    enum { Type = QGraphicsItem::UserType + 2 };
    int type() const { return Type; }


    GraphConnection(QGraphicsItem *parent = 0);
    ~GraphConnection();


    void setPos1(const QPointF &p)  { pos1_ = p; }
    void setPos2(const QPointF &p)  { pos2_ = p; }
    void setPort1(GraphPort *p)     { port1_ = p; port1_->addConnection(this); }
    void setPort2(GraphPort *p)     { port2_ = p; port2_->addConnection(this); }
    GraphPort* port1() const        { return port1_; }
    GraphPort* port2() const        { return port2_; }

    void updatePosFromPorts()       { pos1_ = port1_->scenePos(); pos2_ = port2_->scenePos(); }
    void updatePath();

    //void save(QDataStream&);
    //void load(QDataStream&, const QMap<quint64, GraphEditorPort*> &portMap);

private:
    QPointF pos1_;
    QPointF pos2_;
    GraphPort *port1_;
    GraphPort *port2_;
};

#endif // GRAPHCONNECTION_H


