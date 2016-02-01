#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

#include "NodeItemProxy.h"



NodeItemProxy::NodeItemProxy(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsProxyWidget(parent, wFlags),
      popupShown(false),
      currentPopup(0)
{
    qDebug() << __FUNCTIONW__;

    timeLine = new QTimeLine(250, this);
    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateStep(qreal)));
    connect(timeLine, SIGNAL(stateChanged(QTimeLine::State)), this, SLOT(stateChanged(QTimeLine::State)));
}

QRectF NodeItemProxy::boundingRect() const
{
    return QGraphicsProxyWidget::boundingRect().adjusted(0, 0, 10, 10);
}

void NodeItemProxy::paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const QColor color(0, 0, 0, 64);

    QRectF r = windowFrameRect();
    QRectF right(r.right(), r.top() + 10, 10, r.height() - 10);
    QRectF bottom(r.left() + 10, r.bottom(), r.width(), 10);
    bool intersectsRight = right.intersects(option->exposedRect);
    bool intersectsBottom = bottom.intersects(option->exposedRect);
    if (intersectsRight && intersectsBottom) {
        QPainterPath path;
        path.addRect(right);
        path.addRect(bottom);
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawPath(path);
    } else if (intersectsBottom) {
        painter->fillRect(bottom, color);
    } else if (intersectsRight) {
        painter->fillRect(right, color);
    }

    QGraphicsProxyWidget::paintWindowFrame(painter, option, widget);
}

void NodeItemProxy::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << __FUNCTIONW__;

    QGraphicsProxyWidget::hoverEnterEvent(event);
    scene()->setActiveWindow(this);
    if (timeLine->currentValue() != 1)
        zoomIn();
}

void NodeItemProxy::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << __FUNCTIONW__;

    QGraphicsProxyWidget::hoverLeaveEvent(event);
    if (!popupShown && (timeLine->direction() != QTimeLine::Backward || timeLine->currentValue() != 0)) {
        zoomOut();
    }
}

bool NodeItemProxy::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    qDebug() << __FUNCTIONW__;

    if (watched->isWindow() && (event->type() == QEvent::UngrabMouse || event->type() == QEvent::GrabMouse)) {
        popupShown = watched->isVisible();
        if (!popupShown && !isUnderMouse())
            zoomOut();
    }
    return QGraphicsProxyWidget::sceneEventFilter(watched, event);
}

QVariant NodeItemProxy::itemChange(GraphicsItemChange change, const QVariant &value)
{
    qDebug() << __FUNCTIONW__;

    if (change == ItemChildAddedChange || change == ItemChildRemovedChange) {
        if (change == ItemChildAddedChange) {
            currentPopup = qvariant_cast<QGraphicsItem *>(value);
            currentPopup->setCacheMode(ItemCoordinateCache);
            if (scene())
                currentPopup->installSceneEventFilter(this);
        } else if (scene()) {
            currentPopup->removeSceneEventFilter(this);
            currentPopup = 0;
        }
    } else if (currentPopup && change == ItemSceneHasChanged) {
        currentPopup->installSceneEventFilter(this);
    }
    return QGraphicsProxyWidget::itemChange(change, value);
}

void NodeItemProxy::updateStep(qreal step)
{
    qDebug() << __FUNCTIONW__;

    QRectF r = boundingRect();
    setTransform(QTransform()
                 .translate(r.width() / 2, r.height() / 2)
                 .rotate(step * 30, Qt::XAxis)
                 .rotate(step * 10, Qt::YAxis)
                 .rotate(step * 5, Qt::ZAxis)
                 .scale(1 + 1.5 * step, 1 + 1.5 * step)
                 .translate(-r.width() / 2, -r.height() / 2));
}

void NodeItemProxy::stateChanged(QTimeLine::State state)
{
    qDebug() << __FUNCTIONW__;

    if (state == QTimeLine::Running) {
        if (timeLine->direction() == QTimeLine::Forward)
            setCacheMode(ItemCoordinateCache);
    } else if (state == QTimeLine::NotRunning) {
        if (timeLine->direction() == QTimeLine::Backward)
            setCacheMode(DeviceCoordinateCache);
    }
}

void NodeItemProxy::zoomIn()
{
    qDebug() << __FUNCTIONW__;

    if (timeLine->direction() != QTimeLine::Forward)
        timeLine->setDirection(QTimeLine::Forward);
    if (timeLine->state() == QTimeLine::NotRunning)
        timeLine->start();
}

void NodeItemProxy::zoomOut()
{
    qDebug() << __FUNCTIONW__;

    if (timeLine->direction() != QTimeLine::Backward)
        timeLine->setDirection(QTimeLine::Backward);
    if (timeLine->state() == QTimeLine::NotRunning)
        timeLine->start();
}
