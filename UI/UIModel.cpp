#include "UIModel.h"
#include <RRCConfig/RRCConfig.h>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QRectF>
#include <QGraphicsSceneContextMenuEvent>
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>
#include <RRCCore/PlanningUtil.h>
#include "RRCCommon/Node.h"

UIModel::UIModel(QObject *parent, QComboBox *treeType, QSpinBox *numSteps, QPushButton *run, QLabel *currNumNodes) : QGraphicsScene(parent), m_treeType(treeType), m_numSteps(numSteps) , m_runButton(run), m_currNumNodes(currNumNodes), m_startPos(nullptr), m_goalPos(nullptr) {
    initializeUIModel();
}

Area UIModel::getSceneSize() const {
    return m_sceneSize;
}

std::vector<Area> UIModel::getObstacles() const {
    return m_obstacles;
}

void UIModel::setSceneSize() {
    setSceneRect(0, 0, m_sceneSize.width(), m_sceneSize.height());
    drawBorder();
}

void UIModel::addObstacles() {
    for(unsigned int i = 0; i < m_obstacles.size(); ++i) {
        QGraphicsRectItem *item  = addRect(m_obstacles[i].x(), m_obstacles[i].y(), m_obstacles[i].width(), m_obstacles[i].height());
        item->setBrush(Qt::black);
        addItem(item);
    }
}

void UIModel::onNewPointAdded(float x, float y) {
    QGraphicsEllipseItem *item  = addEllipse(x, y, 2, 2);
    item->setBrush(Qt::blue);
    addItem(item);
}

void UIModel::resetScene() {
    clear();
    addObstacles();
    m_startPos = nullptr;
    m_goalPos = nullptr;
    m_currNumNodes->setText(QString("0"));
}

void UIModel::drawBorder()
{
    // draw scene boundary
    QLineF topLine(sceneRect().topLeft(),
                   sceneRect().topRight());
    QLineF leftLine(sceneRect().topLeft(),
                    sceneRect().bottomLeft());
    QLineF rightLine(sceneRect().topRight(),
                     sceneRect().bottomRight());
    QLineF bottomLine(sceneRect().bottomLeft(),
                      sceneRect().bottomRight());

    QPen myPen = QPen(Qt::red);

    addLine(topLine, myPen);
    addLine(leftLine, myPen);
    addLine(rightLine, myPen);
    addLine(bottomLine, myPen);
}

void UIModel::onNewNodeAdded(Node *newNode) {
    float x = newNode->getPos().x();
    float y = newNode->getPos().y();
    onNewPointAdded(x, y);
    // draw line to its parent
    Node *newNodeParent = newNode->getParent();
    if (newNodeParent != nullptr) {
        QGraphicsLineItem *lineItem = addLine(x, y, newNodeParent->getPos().x(), newNodeParent->getPos().y());
        QPen newPen(Qt::PenStyle::SolidLine);
        newPen.setColor(Qt::blue);
        newPen.setWidth(1);
        lineItem->setPen(newPen);
        addItem(lineItem);
    }

    if (m_shouldDrawNodeIdInGUI) {
        QGraphicsTextItem *textItem = addText(QString::fromStdString(std::to_string(newNode->getId())));
        textItem->setPos(x, y);
        addItem(textItem);
    }
}

void UIModel::initializeUIModel() {
    m_sceneSize = Area(0, 0, RRCConfig::Instance()->initializeFromConfig("worldSettings", "worldWidth", 600), RRCConfig::Instance()->initializeFromConfig("worldSettings", "worldHeight", 600));
    m_obstacles = RRCConfig::Instance()->initializeObstaclesFromConfig();
    m_shouldDrawNodeIdInGUI = RRCConfig::Instance()->initializeFromConfig("Planning", "ShouldDrawNodeIdInGUI", false);
    m_field = Field(m_sceneSize);
}

TreeType UIModel::mapFromQcomboBoxTextToTreeType(const std::string &currStr) const {
    if (currStr == "RRT") return TreeType::RandomRRTTree;
    if (currStr == "RRT*") return TreeType::RandomRRTStarTree;
    if (currStr == "RRC") return TreeType::RandomRRCTree;
    else return TreeType::RandomRRTTree;
}

void UIModel::EnableRelatedWidgetsAfterRun(bool value) {
    m_runButton->setEnabled(value);
    m_treeType->setEnabled(value);
    m_numSteps->setEnabled(value);
}

int UIModel::numSteps() const {
    return m_numSteps->value();
}

TreeType UIModel::treeType() const {
    std::string currTreeType =  m_treeType->currentText().toStdString();
    return mapFromQcomboBoxTextToTreeType(currTreeType);
}

void UIModel::planningFinished() {
    EnableRelatedWidgetsAfterRun(true);
}

void UIModel::setCurrNumOfNodes(int currNumNodes) {
    m_currNumNodes->setText(QString::fromStdString(std::to_string(currNumNodes)));
}

void UIModel::drawNodeForDebug(Node *newNode, Node *nearestNode) {
    float x = newNode->getPos().x();
    float y = newNode->getPos().y();

    QGraphicsEllipseItem *itemNewNode  = addEllipse(x, y, 12, 12);
    itemNewNode->setBrush(Qt::green);
    addItem(itemNewNode);

    float xNear = nearestNode->getPos().x();
    float yNear = nearestNode->getPos().y();

    QGraphicsEllipseItem *itemNearestNode  = addEllipse(xNear, yNear, 3, 3);
    itemNearestNode->setBrush(Qt::red);
    addItem(itemNearestNode);

    QGraphicsLineItem *itemLine = addLine(x, y, xNear, yNear);
    QPen newPen(Qt::PenStyle::DotLine);
    newPen.setColor(Qt::blue);
    newPen.setWidth(0.5);
    itemLine->setPen(newPen);
    addItem(itemLine);
}

void UIModel::drawReturnedPath(const std::vector<Node *> &path)
{
    QPen newPen(Qt::PenStyle::SolidLine);
    newPen.setColor(Qt::red);
    newPen.setWidth(3);

    for(unsigned int i = 1; i < path.size(); ++i)
    {
        QGraphicsLineItem *itemLine = addLine(path[i-1]->getPos().x(), path[i-1]->getPos().y(), path[i]->getPos().x(), path[i]->getPos().y());
        itemLine->setPen(newPen);
        addItem(itemLine);
    }
}

void UIModel::slot_run() {
    EnableRelatedWidgetsAfterRun(false);
    MonitorWrapper::Instance()->getMonitor()->onButtonRunClicked();
}

void UIModel::slot_reset() {
    MonitorWrapper::Instance()->getMonitor()->onButtonResetClicked();
    resetScene();
    setSceneSize();
    drawBorder();
}

void UIModel::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

    QMenu menu(event->widget());
    QString setAsStartPosAction("Set as starting position");
    QString setAsGoalPosAction("Set as goal position");
    menu.addAction(setAsStartPosAction);
    menu.addAction(setAsGoalPosAction);
    QAction *actionChosen = menu.exec(event->screenPos());// show menu in the screen pos and returns the action clicked

    if (actionChosen != nullptr) {
        Position cursorPos((float)event->scenePos().x(), (float)event->scenePos().y());
        // make sure startPos and goalPos are not set in obstacles
        bool cursorPosInObs = false;
        for(unsigned int i = 0; i < m_obstacles.size(); ++i) {
            if (PlanningUtil::isPositionCollideWithObs(m_obstacles[i], cursorPos, cursorPos)) {
                cursorPosInObs = true;
                break;
            }
        }

        if (cursorPosInObs == false) {
            QGraphicsEllipseItem *item  = addEllipse(event->scenePos().x(), event->scenePos().y(), 15, 15);
            if (actionChosen->text() == setAsStartPosAction) {
                removeItem(m_startPos);
                m_startPos = item;
                item->setBrush(Qt::yellow);
            } else if(actionChosen->text() == setAsGoalPosAction) {
                removeItem(m_goalPos);
                m_goalPos = item;
                item->setBrush(Qt::red);
            }
            addItem(item);
        }
    }
}

Position UIModel::startPos() {
    if (m_startPos == nullptr) {
        // if not set, use origin as the default startpos
        m_startPos = addEllipse(0, 0, 15, 15);
        m_startPos->setBrush(Qt::yellow);
        addItem(m_startPos);
    }
    // do not use m_startPos->scenePos() to get the coordinates in scene, it will give the wrong pos
    QRectF boundRectInScene = m_startPos->mapRectToScene(m_startPos->rect());

    return Position((float)boundRectInScene.x(), (float)boundRectInScene.y());
}

Position UIModel::goalPos() {
    if (m_goalPos == nullptr) {
        // if not set, use scene size as the default goalpos
        m_goalPos = addEllipse(m_sceneSize.x(), m_sceneSize.y(), 15, 15);
        m_goalPos->setBrush(Qt::red);
        addItem(m_goalPos);
    }
    QRectF boundRectInScene = m_goalPos->mapRectToScene(m_goalPos->rect());

    return Position((float)boundRectInScene.x(), (float)boundRectInScene.y());
}

Field UIModel::field() const
{
    return m_field;
}



