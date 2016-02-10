#ifndef NODEITEMPROXY_H
#define NODEITEMPROXY_H

#include <QGraphicsProxyWidget>
#include <QTimeLine>

class NodeItemProxy : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    NodeItemProxy(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

private slots:
    //void updateStep(qreal step);
    //void stateChanged(QTimeLine::State);
    //void zoomIn();
    //void zoomOut();

private:
    //QTimeLine *timeLine;
    //bool popupShown;
    //QGraphicsItem *currentPopup;

};

#endif // NODEITEMPROXY_H
