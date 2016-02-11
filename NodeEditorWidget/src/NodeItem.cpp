#include <QtWidgets>
#include <QStyleFactory>


#include "NodeItem.h"
#include "NodeConnection.h"
#include "NodePort.h"




NodeItem::NodeItem(QWidget * widget, Qt::WindowFlags wFlags, QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent, wFlags),
    isMoving(false),
    isMovable(true),
    isResizable(false)
{
    setCacheMode(DeviceCoordinateCache);
	setZValue(1);


/*
    QPainterPath path;

	 //dw
	 //QGroupBox *groupBox = new QGroupBox("GrBox");
	 //QLabel *numberLabel = new QLabel("Telephone number");
	 //QLineEdit *numberEdit = new QLineEdit;
	 //QFormLayout *layout = new QFormLayout;
	 //layout->addRow(numberLabel, numberEdit);
	 //groupBox->setLayout(layout);
	 QFormLayout *layout2 = new QFormLayout;
	 //layout2->addRow(groupBox);

	 QLabel* out0 = new QLabel("out0");
	 out0->setAlignment(Qt::AlignRight);
	 QLabel* in0 = new QLabel("in0");
	 layout2->addRow(in0, out0);
	 QLabel* in1 = new QLabel("in1");
	 layout2->addRow(in1);
	 QLabel* in2 = new QLabel("in2");
	 layout2->addRow(in2);
	 QLabel* inout0 = new QLabel("inOut0");
	 inout0->setAlignment(Qt::AlignRight);
	 layout2->addRow(inout0);

	 //QSpinBox ( int minValue, int maxValue, int step = 1, QWidget * parent = 0, const char * name = 0 )
	 QSpinBox* spinBox = new QSpinBox();
	 spinBox->setMinimum(0);
	 spinBox->setMaximum(9);
	 layout2->addRow(spinBox);

	 QDialog *dialog1 = new QDialog();
	 //QFrame *dialog1 = new QFrame();
	 //QGroupBox* dialog1 = new QGroupBox("A QGroupBox");
	 dialog1->setLayout(layout2);
	 //dialog1->setLayout(groupBox);
	 //this->setWidget(groupBox);
	 //dw will this fix deletion not called on close?
	 dialog1->setAttribute(Qt::WA_DeleteOnClose);
	 this->setWidget(dialog1);
*/
    QDialog * itemDialog = new QDialog();
    QToolBox * toolBox  = new QToolBox();
    QHBoxLayout * newLayout = new QHBoxLayout();
    if (widget) {
        toolBox->addItem(widget, "Filter settings");
        toolBox->addItem(nullptr, "Ports");
        toolBox->setItemEnabled(0, true);
        toolBox->setItemEnabled(1, true);
        toolBox->adjustSize();
    }

    newLayout->addWidget(toolBox);
    newLayout->setSizeConstraint(QLayout::SetFixedSize);
    itemDialog->setLayout(newLayout);
    itemDialog->adjustSize();
    //itemDialog->resize(300,300);

    setWidget(itemDialog);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}



NodeItem::~NodeItem()
{
    //removeWigetFromPorts();
    //deleteConnections();

    QWidget * embeddedWidget = widget();
    setWidget(0);
    delete embeddedWidget;
}



QRectF NodeItem::boundingRect() const
{
    QRectF rect(QGraphicsProxyWidget::boundingRect());
    qreal extra = 3;
    rect = rect.normalized().adjusted(-extra, 0, extra, 0);
    //rect.setWidth(rect.width() - 2 * (mMaxRadius + 1));
    //rect.setX(rect.x() + (mMaxRadius + 1));
    //rect.setWidth(rect.width() - 4);
    //rect.setX(rect.x() + 2);
    return rect;
}

QPainterPath NodeItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void NodeItem::addPort(NodePort* port)
{
    ports.append(port);
    updatePortsPos();
	prepareGeometryChange();
}


void NodeItem::deleteConnections()
{
    foreach (NodePort *port, ports) {
		//dw problem: label already deleted but connector tries to enable it?
        port->deleteConnections();
    }

	//dw good location?, needed?
	//this->scene()->removeItem(this);
}


void NodeItem::removeWigetFromPorts()
{
    foreach (NodePort *c, ports) {
		//dw problem: label already deleted but connector tries to enable it?
        c->removeWidget();
    }
}


void NodeItem::updatePortsPos() {
    foreach (NodePort *port, ports) {
        port->updatePosition();
    }
}


void NodeItem::debugPaint(QPainter *painter)
{
	static int i = 0, j=0, k=0;
    painter->fillRect(boundingRect(), /*Qt::green*/ QColor(i=(i+19)%256 , j=(j+51)%256, k=(k+11)%256));
}



//void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
//{
//    debugPaint(painter);
//	QGraphicsProxyWidget::paint(painter, option, w);
//}


bool NodeItem::shouldMoveNode(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointer<QWidget> hitWidget = widget()->childAt(mouseEvent->pos().toPoint());
    if ( (hitWidget == NULL) ||
         (hitWidget->inherits("QDialog"))  ||
         (hitWidget->inherits("QFrame"))   ||
         (hitWidget->inherits("QGroupBox")))  {
            return true;
    }
    return false;
}


QVariant NodeItem::itemChange(GraphicsItemChange change, //dw FIXME: needs much cleanup
                     const QVariant &value)
{
   if (change == QGraphicsItem::ItemSelectedChange ||
       change == QGraphicsItem::ItemTransformChange ||
       change == QGraphicsItem::ItemScaleChange ||
       change == QGraphicsItem::ItemSendsGeometryChanges ||
       change == QGraphicsItem::ItemMatrixChange ||
       change == QGraphicsItem::ItemPositionHasChanged ||
       change == QGraphicsItem::ItemPositionChange ) {
           updatePortsPos();
   }

    return QGraphicsProxyWidget::itemChange(change, value);
}






void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << __FUNCTION__;

    if (shouldMoveNode(mouseEvent)) {
        QGraphicsItem::mousePressEvent(mouseEvent);
        isMoving = true;
        scene()->clearSelection();
        scene()->clearFocus();
        setSelected(true);
    }
    else {
        QGraphicsProxyWidget::mousePressEvent(mouseEvent);
    }
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    qDebug() << __FUNCTION__;
    QGraphicsProxyWidget::mouseMoveEvent(mouseEvent);

    if (isMoving) {
		QGraphicsItem::mouseMoveEvent(mouseEvent);

		//dw667 backmerge: was active
		//dw new5
        //foreach (NodeConnector *con, connectors) {
        //	//dw667 backmerge: was active
        //	//con->updatePositionGeometry();
        //	//dw667 backmerge: new
        //	con->updatePosition();
        //}
	}

	//scene()->clearSelection();
	//setSelected(true);
    //updateConnectorsPos();

}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << __FUNCTION__;

	if (isMoving) {
		isMoving = false;
	}

	//call both always to lose no events and to not have to do the same shit for clicks too
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
    QGraphicsProxyWidget::mouseReleaseEvent(mouseEvent);
	scene()->clearSelection();
	setSelected(true);
    //updateConnectorsPos();
}




