#include "UIModel.h"
#include <RRCConfig/RRCConfig.h>
#include <QGraphicsRectItem>
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>

UIModel::UIModel(QObject *parent) : QGraphicsScene(parent) {
    InitializeUIModel();
}

Area UIModel::GetSceneSize() {
    return m_sceneSize;
}

std::vector<Area> UIModel::GetObstacles() {
    return m_obstacles;
}

void UIModel::SetSceneSize() {
    setSceneRect(0, 0, m_sceneSize.width(), m_sceneSize.height());
}

void UIModel::AddObstacles() {
    for(unsigned int i = 0; i < m_obstacles.size(); ++i) {
        QGraphicsRectItem *item  = addRect(m_obstacles[i].x(), m_obstacles[i].y(), m_obstacles[i].width(), m_obstacles[i].height());
        item->setBrush(Qt::black);
        addItem(item);
    }
}

void UIModel::slot_run()
{
    MonitorWrapper::Instance()->GetMonitor()->OnButtonRunClicked();
}

void UIModel::OnNewPointAdded(float x, float y)
{
    QGraphicsEllipseItem *item  = addEllipse(x, y, 10, 10);
    item->setBrush(Qt::blue);
    addItem(item);
}

void UIModel::InitializeUIModel() {
    m_sceneSize = Area(0, 0, RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldWidth", 100), RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldHeight", 100));
    m_obstacles = RRCConfig::Instance()->InitializeObstaclesFromConfig();
}

