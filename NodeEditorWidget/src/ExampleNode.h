#pragma once

#include <QtWidgets>

#include "NodeItem.h"
#include "NodePort.h"
#include "NodeConnection.h"


class ExampleNode : public NodeItem {
public:
    QGridLayout *innerGridLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *bottomLayout;


    ExampleNode(QGraphicsScene *scene,
                QMenu *contextMenu = 0,
                QGraphicsItem *parent = 0,
                Qt::WindowFlags wFlags = 0);

    void setWidget(QWidget *widget);
    void addPortAndLabel(QString name,
                         NodePort::PortType t,
                         NodePort::PortAlignment align);

    //void serialize(QTextStream& out);
    //void deserialize(QTextStream& out, QMap<int, ExampleBaseNode*>& map);
};




