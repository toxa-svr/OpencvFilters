#ifndef GRAPHPORT_H
#define GRAPHPORT_H

#include <QGraphicsPathItem>

class GraphNode;
class GraphConnection;

class GraphPort : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 1 };
	enum { NamePort = 1, TypePort = 2 };

    GraphPort(QGraphicsItem *parent = 0);
    ~GraphPort();

    int type() const                { return Type; }

    void setNode(GraphNode* node)   { node_ = node; }
    GraphNode* getNode() const      { return node_; }

    void setName(const QString &n)  { name_ = n; label_->setPlainText(n); }
    const QString& name() const     { return name_; }

    #define PORT_RADIUS_DEFAULT 5
    void setRadius (int radius)     { radius_ = radius; }
    int radius() const              { return radius_; }

    void setIsOutput(bool o);
    bool isOutput() const           { return isOutput_; }

    void setFlags(int);
    int flags() const               { return portFlags_; }

    void setPtr(quint64 p)          { ptr_ = p; }
    quint64 ptr() const             { return ptr_; }

    bool isConnectedWith(GraphPort*) const;
    void addConnection(GraphConnection* conn)    { connections_.append(conn); }
    void removeConnection(GraphConnection* conn) { connections_.removeOne(conn);}

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    GraphNode*          node_;
    QString             name_;
    bool                isOutput_;
    QGraphicsTextItem*  label_;
    int                 radius_;
    int                 margin_;
    QVector<GraphConnection*> connections_;
    int                 portFlags_;
    quint64             ptr_;
};

#endif // GRAPHPORT_H


