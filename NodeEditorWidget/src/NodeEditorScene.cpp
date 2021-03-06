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

    setStickyFocus(true); // clicking into the scene background will clear focus
}


void NodeEditorScene::deleteSelectedItems()
{
    QList<QGraphicsItem*> itemsToDelete = selectedItems();

    if (itemsToDelete.isEmpty()) {
        qDebug() << "No items selected";
        return;
    }

    foreach(QGraphicsItem* item, itemsToDelete)
    {
        removeItem(item);
        delete item;
    }
}


/*
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


            if (start->portType() != NodePort::In) {
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
    qDebug() << __FUNCTION__;

    if (tmpConnection != 0) {

		//simple right/left handling
        if (tmpConnection->startPort()->mapToScene(0,0).x() < tmpConnection->endPort()->mapToScene(0,0).x()) {
            if (tmpPort == tmpConnection->endPort())
                tmpPort->setPortAlignment(NodePort::PortAlignment::Left);// right = false;
			else
				//tmpConnector->right = true;
                tmpPort->setPortAlignment(NodePort::PortAlignment::Right);
		}
		else {
            if (tmpPort == tmpConnection->endPort())
				//tmpConnector->right = true;
                tmpPort->setPortAlignment(NodePort::PortAlignment::Right);
			else
				//tmpConnector->right = false;
                tmpPort->setPortAlignment(NodePort::PortAlignment::Left);
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
            if (existingPort->portType() == NodePort::InOut) {
				//switch if non matching
                if ((node->portType() == NodePort::Out && tmpConnection->startPort() == existingPort)
                    || (node->portType() == NodePort::In && tmpConnection->endPort() == existingPort)) {
					//tmpConnector->setConnectorType(node->connectorType());
                    NodePort* old1 = tmpConnection->startPort();
                    NodePort* old2 = tmpConnection->endPort();
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
            else if (node->portType() != NodePort::InOut && node->portType() == existingPort->portType()) {
				return;
			}

			node->setHighlight(true);
            //node->updatePosition();
            //node->update();
			//dw667 backmerge:
			node->updatePosition();
			node->update();
			
            tmpPort->setPortAlignment(node->portAlignment());
            tmpPort->setPortType(node->portType());
			//FIXME: make configurable
            tmpConnection->setBidirectional(true);

            tmpPort->updatePosition();
            tmpPort->update();
			lastHighlighted = node;
		}
		else if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
            //lastHighlighted->updatePosition();
            //lastHighlighted->update();
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
    qDebug() << __FUNCTION__;

    if (tmpConnection != 0) {
        NodePort* startC = tmpConnection->startPort();
        NodePort* endC = tmpConnection->endPort();
		QPointF startPos(startC->mapToScene(0, 0));
		QPointF endPos(endC->mapToScene(0, 0));
		//QPointF endPos(mouseEvent->scenePos());

        tmpConnection->startPort()->setHighlight(false);
        tmpConnection->endPort()->setHighlight(false);
        //tmpArrow->startConnector()->updatePosition();
        //tmpArrow->startConnector()->update();
        //tmpArrow->endConnector()->updatePosition();
        //tmpArrow->endConnector()->update();

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
            if (!((startConnector->portType() == NodePort::In && endConnector->portType() == NodePort::In) || (startConnector->portType() == NodePort::Out && endConnector->portType() == NodePort::Out)))
			{
				NodeConnection *arrow = new NodeConnection(startConnector, endConnector, NULL, this);
                arrow->setColor(QColor(100,100,100)); // settings.connectionLineColor
				startConnector->addConnection(arrow);
				endConnector->addConnection(arrow);
				arrow->setZValue(-1000.0);

                arrow->startPort()->setHighlight(false);
                arrow->endPort()->setHighlight(false);
                arrow->startPort()->update();
                arrow->endPort()->update();
			}

//            arrow->setZValue(2.0);
            //addItem(arrow);
			startConnector->setHighlight(false);
			endConnector->setHighlight(false);
            //arrow->updatePosition();
			//dw new

            //startConnector->updatePosition();
            //startConnector->update();
            //endConnector->updatePosition();
            //endConnector->update();
        }
			//NOTE: assumtion that lastHighlighted is never deleted while drawing lines, otherwise pointer can go to nirvana (TODO: can we use this assumtion?)
		if (lastHighlighted != NULL) {
			lastHighlighted->setHighlight(false);
            //lastHighlighted->updatePosition();
            //lastHighlighted->update();
			lastHighlighted = NULL;
		}
		return;
    }

    //line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


*/


