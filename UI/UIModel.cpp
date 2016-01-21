#include "UIModel.h"
#include <RRCConfig/RRCConfig.h>
#include <QGraphicsRectItem>
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>

UIModel::UIModel(QObject *parent) : QGraphicsScene(parent) {
    this->InitializeUIModel();
}

Area UIModel::GetSceneSize() {
    return this->sceneSize;
}

std::vector<Area> UIModel::GetObstacles() {
    return this->obstacles;
}

void UIModel::SetSceneSize() {
    setSceneRect(0, 0, sceneSize.width(), sceneSize.height());
}

void UIModel::AddObstacles() {
    for(unsigned int i = 0; i < obstacles.size(); ++i) {
        QGraphicsRectItem *item  = addRect(obstacles[i].x(), obstacles[i].y(), obstacles[i].width(), obstacles[i].height());
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
    this->sceneSize = Area(0, 0, RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldWidth", 100), RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldHeight", 100));
    this->obstacles = RRCConfig::Instance()->InitializeObstaclesFromConfig();
}

