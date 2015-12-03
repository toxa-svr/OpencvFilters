#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsPathItem>

class GraphPort;
class GraphConnection;


//-------------------------------------------------
// Settings for each node representation.
// Node shape is always rounded rectangle with title.
//
// Collapsed node's mode - small rectangle with a title and ports only.
// Expanded node's mode  - full size rectangle which chan show all another elements,
//                         according to the global widget's settings
//                         (another elements are: small title/port names/icon/internal widgets/etc.)
//-------------------------------------------------
class GraphNodeSettings
{
public:

    GraphNodeSettings():
        isCollapsed(false),
        title("Node title"),
        smallTitle("Node small title"),
        icon(nullptr),
        widget(nullptr)  {}

    bool isCollapsed;     // show small nodes with a title only or full size nodes
    QString title;
    QString smallTitle;
    QPixmap* icon;
    QWidget* widget;

};





//-------------------------------------------------
class GraphNode : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 3 };
    int type() const { return Type; }

    GraphNode(QGraphicsItem *parent = 0);
    GraphNode(const QWidget &widget, QGraphicsItem *parent = 0);
    GraphNode(const QString &title, const QString &smallTitle, const QPixmap *icon, const QWidget *widget, const bool isCollapsed, QGraphicsItem *parent = 0);
    GraphNode(const GraphNodeSettings &settings, QGraphicsItem *parent = 0);

    QVector<GraphPort*> ports();
    GraphPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
    void addInputPort(const QString &name)        { addPort(name, false); }
    void addOutputPort(const QString &name)       { addPort(name, true); }
    void addInputPorts(const QStringList &names)  { foreach(QString n, names) addPort(n, false); }
    void addOutputPorts(const QStringList &names) { foreach(QString n, names) addPort(n, true); }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Set/get titles, icon, widget, settings
    void setSettings(const GraphNodeSettings &settings) { settings_ = settings; }
    GraphNodeSettings settings() const { return settings_;}
    void setTitle(const QString title) { settings_.title = (QString)title; }
    QString title() const { return settings_.title;}
    void setSmallTitle(const QString smallTitle) { settings_.smallTitle = (QString)smallTitle; }
    QString smallTitle() const { return settings_.smallTitle; }
    void setIcon(const QPixmap *icon) { settings_.icon = (QPixmap*)icon; }
    QPixmap* icon() const { return settings_.icon;}
    void setWidget(const QWidget *widget) { settings_.widget = (QWidget*)widget; }
    QWidget* widget() const { return settings_.widget;}
    void setCollpsed(const bool collapsed) { settings_.isCollapsed = collapsed; }
    bool collapsed() const { return settings_.isCollapsed;}



    // TODO
    //void save();
    //void load();

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    // Settings with titles, widget pointer, icon pointer
    GraphNodeSettings settings_;

    // Position and values that can be changed from GraphicView
    int horzMargin_;
    int vertMargin_;
    int width_;
    int height_;

    // Called in constructor to create node's widget
    void initNodeWidget();
};

#endif // GRAPHNODE_H


