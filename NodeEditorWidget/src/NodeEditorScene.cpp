#include <QtGui>
#include <QtWidgets>
#include <QGraphicsSceneEvent>
#include <QDebug>

#include "NodeEditorScene.h"
#include "NodeItem.h"
#include "NodeConnection.h"
#include "NodePort.h"



NodeEditorScene::NodeEditorScene(QWidget *parent)
    : QGraphicsScene(parent)
{
    tmpConnection = nullptr;
    tmpPort = nullptr;
    lastHighlighted = nullptr;
    conn = nullptr;

    //setScene(scene); // set QGraphicsScene for this QGraphicsView
    //setRenderHint(QPainter::Antialiasing, true);
    //setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //scene.installEventFilter(this); // add event filter for QGraphicsScene to handle events here
}



void NodeEditorScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << __FUNCTION__;

    if (mouseEvent->button() != Qt::LeftButton)
        return;

    QList<QGraphicsItem *> startConnectors = items(mouseEvent->scenePos());
    foreach(QGraphicsItem * g, startConnectors) {
        if (g->type() == NodePort::Type) {
            NodePort* start = dynamic_cast<NodePort*>(g);
            //dw ugly
            if (start->mSingleConnection) {
                start->deleteConnections();
            }

            tmpPort = new NodePort(nullptr, this, nullptr, NodePort::InOut);
            tmpPort->setPos(mouseEvent->scenePos());
            //dw needed? addItem(tmpConnector);

            // TODO debug draw
            //if (settings.debugDraw) {
                tmpPort->mRadius = 5;
            //}
            //else {
            //    tmpPort->setVisible(false);
            //    tmpPort->mRadius = 0;
            //}


            if (start->connectorType() != NodePort::In) {
                tmpConnection = new NodeConnection(start, tmpPort, NULL, this);
            }
            else {
                tmpConnection = new NodeConnection(tmpPort, start, NULL, this);
            }
            //dw needed? addItem(tmpArrow);
            start->setHighlight(true);
            existingPort = start;


            existingPort->updatePosition();
            existingPort->update();
            tmpPort->updatePosition();
            tmpPort->update();
            tmpConnection->updatePosition();
            tmpConnection->update();

            //dw667 backmerge: was commented
            //QGraphicsScene::mousePressEvent(mouseEvent);
            return;
            //addItem(tmpArrow);
            //if (
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}


void NodeEditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (tmpConnection != 0) {

		//simple right/left handling
        if (tmpConnection->startConnector()->mapToScene(0,0).x() < tmpConnection->endConnector()->mapToScene(0,0).x()) {
            if (tmpPort == tmpConnection->endConnector())
                tmpPort->setConnectorAlignment(NodePort::PortAlignment::Left);// right = false;
			else
				//tmpConnector->right = true;
                tmpPort->setConnectorAlignment(NodePort::PortAlignment::Right);
		}
		else {
            if (tmpPort == tmpConnection->endConnector())
				//tmpConnector->right = true;
                tmpPort->setConnectorAlignment(NodePort::PortAlignment::Right);
			else
				//tmpConnector->right = false;
                tmpPort->setConnectorAlignment(NodePort::PortAlignment::Left);
		}

		// if we hit a connecor, highlight it and take 'right' over, switch in and out if neccessary
		QList<QGraphicsItem *> intersectedItems = items(mouseEvent->scenePos());
        while(intersectedItems.count() && (intersectedItems.first() == tmpConnection || intersectedItems.first() == tmpPort || intersectedItems.first()->type() != NodePort::Type)) {
            intersectedItems.removeFirst();
		}
        if (intersectedItems.count() && intersectedItems.first() != tmpPort && intersectedItems.first() != existingPort) {
			//dw thats how a cast should look like
            NodePort *node = qgraphicsitem_cast<NodePort *>(intersectedItems.first());
			//ugly direction handling, only case where a switch is possible
            if (existingPort->connectorType() == NodePort::InOut) {
				//switch if non matching
                if ((node->connectorType() == NodePort::Out && tmpConnection->startConnector() == existingPort)
                    || (node->connectorType() == NodePort::In && tmpConnection->endConnector() == existingPort)) {
					//tmpConnector->setConnectorType(node->connectorType());
                    NodePort* old1 = tmpConnection->startConnector();
                    NodePort* old2 = tmpConnection->endConnector();
					//dw needed? removeItem(tmpArrow);
					//dw667 backmerge: to slow if connector is child of item
					//removeItem(tmpArrow);
                    delete tmpConnection;
                    tmpConnection = new NodeConnection(old2, old1, NULL, this);
					//dw667 backmerge: to slow if connector is child of item
					//addItem(tmpArrow);
				}
			}
			//check if uncompatible
            else if (node->connectorType() != NodePort::InOut && node->connectorType() == existingPort->connectorType()) {
				return;
			}

			node->setHighlight(true);
			/*node->updatePosition();
			node->update();*/
			//dw667 backmerge:
			node->updatePosition();
			node->update();
			
            tmpPort->setConnectorAlignment(node->connectorAlignment());
            tmpPort->setConnectorType(node->connectorType());
			//FIXME: make configurable
            tmpConnection->setBidirectional(true);

            tmpPort->updatePosition();
            tmpPort->update();
			lastHighlighted = node;
		}
		else if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
			/*lastHighlighted->updatePosition();
			lastHighlighted->update();*/
			//dw667 backmerge:
			lastHighlighted->updatePosition();
			lastHighlighted->update();
			
			lastHighlighted = NULL;
            tmpPort->updatePosition();
            tmpPort->update();
		}

        //QLineF newLine(line->line().p1(), mouseEvent->scenePos());
		//line->setLine(newLine);
		//tmpConnector = new NodeConnector(NULL, scene, NULL, NodeConnector::InOut);
		//tmpConnector-> = new NodeConnector(NULL, scene, NULL, NodeConnector::InOut);
        tmpPort->setPos(mouseEvent->scenePos());
        tmpConnection->updatePosition();
        tmpConnection->update();
		//dw667 backmerge: was commented
        tmpPort->updatePosition();
		
        tmpPort->update();
		return;
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}


void NodeEditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (tmpConnection != 0) {
        NodePort* startC = tmpConnection->startConnector();
        NodePort* endC = tmpConnection->endConnector();
		QPointF startPos(startC->mapToScene(0, 0));
		QPointF endPos(endC->mapToScene(0, 0));
		//QPointF endPos(mouseEvent->scenePos());

        tmpConnection->startConnector()->setHighlight(false);
        tmpConnection->endConnector()->setHighlight(false);
		/*tmpArrow->startConnector()->updatePosition();
		tmpArrow->startConnector()->update();
		tmpArrow->endConnector()->updatePosition();
		tmpArrow->endConnector()->update();*/

		QList<QGraphicsItem *> startConnectors = items(startPos);
        while(startConnectors.count() && (startConnectors.first() == tmpConnection || startConnectors.first() == tmpPort || startConnectors.first()->type() != NodePort::Type)) {
            startConnectors.removeFirst();
		}
		QList<QGraphicsItem *> endConnectors = items(endPos);
        while(endConnectors.count() && (endConnectors.first() == tmpConnection || endConnectors.first() == tmpPort || endConnectors.first()->type() != NodePort::Type)) {
            endConnectors.removeFirst();
		}

		//removeItem(tmpArrow);

        delete tmpConnection;
        tmpConnection = 0;
		//dw now done in dtor, good idea?
		//dw new
		//removeItem(tmpConnector);
        delete tmpPort;
		//tmpConnector->deleteLater();
        tmpPort = 0;
        
		if (startConnectors.count() > 0 && endConnectors.count() > 0 &&
            startConnectors.first()->type() == NodePort::Type &&
            endConnectors.first()->type() == NodePort::Type &&
            startConnectors.first() != endConnectors.first())
		{
            NodePort *startConnector =
                qgraphicsitem_cast<NodePort *>(startConnectors.first());
            NodePort *endConnector =
                qgraphicsitem_cast<NodePort *>(endConnectors.first());

			//dw new: verify again:
            if (!((startConnector->connectorType() == NodePort::In && endConnector->connectorType() == NodePort::In) || (startConnector->connectorType() == NodePort::Out && endConnector->connectorType() == NodePort::Out)))
			{
				NodeConnection *arrow = new NodeConnection(startConnector, endConnector, NULL, this);
                arrow->setColor(QColor(100,100,100)/*settings.connectionLineColor*/);
				startConnector->addConnection(arrow);
				endConnector->addConnection(arrow);
				arrow->setZValue(-1000.0);

				arrow->startConnector()->setHighlight(false);
				arrow->endConnector()->setHighlight(false);
				arrow->startConnector()->update();
				arrow->endConnector()->update();
			}

//            arrow->setZValue(2.0);
            //addItem(arrow);
			startConnector->setHighlight(false);
			endConnector->setHighlight(false);
            //arrow->updatePosition();
			//dw new

			/*startConnector->updatePosition();
			startConnector->update();
			endConnector->updatePosition();
			endConnector->update();*/
        }
			//NOTE: assumtion that lastHighlighted is never deleted while drawing lines, otherwise pointer can go to nirvana (TODO: can we use this assumtion?)
		if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
			/*lastHighlighted->updatePosition();
			lastHighlighted->update();*/
			lastHighlighted = NULL;
		}
		return;
    }

    //line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


bool NodeEditorScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}


NodeItem * NodeEditorScene::createNode () {
    NodeItem *node2 = new NodeItem(0);
    //this->addItem(node2);
    //node2->setPos(mouseEvent->scenePos());
    return node2;
}


//void NodeEditorWidget::editorLostFocus(DiagramTextItem *item)
//{
//    QTextCursor cursor = item->textCursor();
//    cursor.clearSelection();
//    item->setTextCursor(cursor);
//    if (item->toPlainText().isEmpty()) {
//        removeItem(item);
//        item->deleteLater();
//    }
//}
//void setItemType(DiagramItem::DiagramType type)
//{
//    mItemType = type;
//}


