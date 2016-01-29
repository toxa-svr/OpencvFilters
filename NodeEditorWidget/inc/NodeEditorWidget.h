#pragma once

#include <QtWidgets>


//-------------------------------------------------
// Settings for whole Widget
//-------------------------------------------------
struct NodeEditorSettings
{
    // Widget representation
    bool debugDraw;

    // Node representation
    bool showNodeTitle;
    bool showNodeSmallTitle;
    bool showNodeIcon;
    bool showNodeWidget;
    bool showNodePortNames;

    // Port representation

    // Connection representation
    QColor connectionLineColor;
};




class NodeEditorWidget : public QGraphicsView
{
    Q_OBJECT

public:
    NodeEditorWidget (QWidget* parent = nullptr);

    //QGraphicsItem * addNode();
    //QGraphicsItem * addNode(const QWidget &widget);
    //QGraphicsItem * addNode(const QString &title, const QString &smallTitle, const QPixmap &icon, const QWidget &widget, const bool isCollapsed);
    //QGraphicsItem * addPort();
    //QGraphicsItem * addConnection();
    //QGraphicsItem *itemAt(const QPointF&);
    //QGraphicsItem * createGraphNode();
    //void save(QDataStream &ds);
    //void load(QDataStream &ds);

private:
    NodeEditorSettings settings;

};















