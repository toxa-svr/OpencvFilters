#include <QtGui>
#include <QtWidgets>
#include <QGraphicsSceneEvent>
#include <QDebug>

#include "../inc/NodeEditorView.h"
#include "NodeItem.h"
#include "NodeConnection.h"
#include "NodePort.h"


//--------------------------------------------------------------------------------
// Node Editor View
//--------------------------------------------------------------------------------
#ifndef QT_NO_WHEELEVENT
void NodeEditorView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0) {
            ownerNodeEditorWidget->zoomIn(6);
        }
        else {
            ownerNodeEditorWidget->zoomOut(6);
        }
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}
#endif





//--------------------------------------------------------------------------------
// Widget for node editor
//--------------------------------------------------------------------------------

NodeEditorWidget::NodeEditorWidget(QGraphicsScene *scene, QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);

    // Create and configure QGraphicsView, set Scene for it
    nodeEditorView = new NodeEditorView(this);
    nodeEditorView->setScene(scene);
    nodeEditorView->setRenderHint(QPainter::Antialiasing, true);
    nodeEditorView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    nodeEditorView->setDragMode(QGraphicsView::ScrollHandDrag);
    nodeEditorView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    nodeEditorView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    nodeEditorView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //nodeEditorView->setBackgroundBrush(QPixmap(":/No-Ones-Laughing-3.jpg"));

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);


    zoomInButton = new QToolButton;
    zoomInButton->setAutoRepeat(true);
    zoomInButton->setAutoRepeatInterval(33);
    zoomInButton->setAutoRepeatDelay(0);
    //zoomInButton->setIcon(QPixmap(":/zoomin.png"));
    zoomInButton->setIconSize(iconSize);
    zoomInButton->setToolTip("Zoom In");

    zoomOutButton = new QToolButton;
    zoomOutButton->setAutoRepeat(true);
    zoomOutButton->setAutoRepeatInterval(33);
    zoomOutButton->setAutoRepeatDelay(0);
    //zoomOutButton->setIcon(QPixmap(":/zoomout.png"));
    zoomOutButton->setIconSize(iconSize);
    zoomOutButton->setToolTip("Zoom Out");

    zoomResetButton = new QToolButton;
    zoomResetButton->setText(tr("0"));
    zoomResetButton->setEnabled(true);
    //zoomResetButton->setIcon(QPixmap(":/zoomreset.png"));
    zoomResetButton->setToolTip("Reset Zoom to 100%");

    zoomSlider = new QSlider;
    zoomSlider->setFixedHeight(200);
    zoomSlider->setMinimum(1);
    zoomSlider->setMaximum(150);
    zoomSlider->setValue(100);
    zoomSlider->setTickPosition(QSlider::NoTicks);
    zoomSlider->setToolTip("Ctrl+Scroll to zoom");


    // Zoom slider layout
    QVBoxLayout *zoomSliderLayout = new QVBoxLayout;
    zoomSliderLayout->addWidget(zoomInButton);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomOutButton);


    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(nodeEditorView, 1, 0);
    topLayout->addLayout(zoomSliderLayout, 1, 1);
    topLayout->addWidget(zoomResetButton, 2, 1);
    setLayout(topLayout);

    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(zoomResetButton, SIGNAL(clicked()), this, SLOT(zoomReset()));

    setupMatrix();
}


//--------------------------------------------------------------------------------
void NodeEditorWidget::zoomReset()
{
    zoomSlider->setValue(100);
    setupMatrix();
    nodeEditorView->ensureVisible(QRectF(0, 0, 0, 0));
}

//--------------------------------------------------------------------------------
void NodeEditorWidget::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 100) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);
    nodeEditorView->setMatrix(matrix);
}



