#ifndef GRAPHEDITORWIDGET_H
#define GRAPHEDITORWIDGET_H

#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>

#include "GraphPort.h"
#include "GraphNode.h"
#include "GraphConnection.h"



class GraphEditorWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphEditorWidget (QWidget* parent = nullptr);

    void addNode();
    void addConnection();

    void install(QGraphicsScene *scene);
    bool eventFilter(QObject *, QEvent *);

    //void save(QDataStream &ds);
    //void load(QDataStream &ds);

    QGraphicsItem *itemAt(const QPointF&);

private:
    QGraphicsScene scene;
    GraphConnection *conn;
    //GraphNode *selBlock;
};

#endif // GRAPHEDITORWIDGET_H

