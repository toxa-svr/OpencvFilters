#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsPathItem>

class GraphPort;
class GraphConnection;


//-------------------------------------------------
// Settings for node representation.
//      Node shape is always rounded rectangle with title.
//      Additional title, icon or widget can be displayed selectively.
//-------------------------------------------------
class GraphNodeSettings
{
public:

    GraphNodeSettings():isCollapsed(false),
                        showSmallTitle(true),
                        showIcon(true),
                        showWidget(true) {}

    bool isCollapsed;     // show small nodes with a title only
    bool showSmallTitle;
    bool showIcon;
    bool showWidget;
    bool showPortNames;   //show port names
};



struct GraphNodeStyle
{
    int rounding;
//    Qt::green

};



//-------------------------------------------------
class GraphNode : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 3 };
    int type() const { return Type; }

    GraphNode(QGraphicsItem *parent = 0);

    QVector<GraphPort*> ports();
    GraphPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
    void addInputPort(const QString &name)        { addPort(name, false); }
    void addOutputPort(const QString &name)       { addPort(name, true); }
    void addInputPorts(const QStringList &names)  { foreach(QString n, names) addPort(n, false); }
    void addOutputPorts(const QStringList &names) { foreach(QString n, names) addPort(n, true); }

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Set/get titles, icon, widget, settings
    void setTitle(const QString title) { title_ = (QString)title; }
    QString title() const { return title_;}
    void setSmallTitle(const QString smallTitle) { smallTitle_ = (QString)smallTitle; }
    QString smallTitle() const { return smallTitle_; }
    void setIcon(const QPixmap *icon) { icon_ = (QPixmap*)icon; }
    QPixmap* icon() const { return icon_;}
    void setWidget(const QWidget *widget) { widget_ = (QWidget*)widget; }
    QWidget* widget() const { return widget_;}
    void setSettings(const GraphNodeSettings &settings) { settings_ = settings; }
    GraphNodeSettings settings() const { return settings_;}

    // TODO
    //void save();
    //void load();

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:

    QString title_;
    QString smallTitle_;
    QPixmap* icon_;
    QWidget* widget_;
    GraphNodeSettings settings_;

    int horzMargin_;
    int vertMargin_;
    int width_;
    int height_;
};

#endif // GRAPHNODE_H


