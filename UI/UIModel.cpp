#include "UIModel.h"
#include <RRCConfig/RRCConfig.h>
#include <QGraphicsRectItem>
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>

UIModel::UIModel(QObject *parent) : QGraphicsScene(parent) {
    Area temp(std::vector<float>(2, 0));
    this->sceneSize = temp;
    this->InitializeUIModel();
}

Area UIModel::GetSceneSize() {
    return this->sceneSize;
}

std::vector<Area> UIModel::GetObstacles() {
    return this->obstacles;
}

void UIModel::SetSceneSize() {
    setSceneRect(0, 0,  this->sceneSize.GetNthDimLimit(1), this->sceneSize.GetNthDimLimit(2));
}

void UIModel::AddObstacles() {
    for(unsigned int i = 0; i < obstacles.size(); ++i) {
        QGraphicsRectItem *item  = addRect(obstacles[i].GetNthDim(1), obstacles[i].GetNthDim(2), obstacles[i].GetNthDimLimit(1), obstacles[i].GetNthDimLimit(2));
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
    this->sceneSize.SetNthDim(1, 0);
    this->sceneSize.SetNthDim(2, 0);
    this->sceneSize.SetNthDimLimit(1, RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldWidth", 100));
    this->sceneSize.SetNthDimLimit(2, RRCConfig::Instance()->InitializeFromConfig("worldSettings", "worldHeight", 100));
    this->obstacles = RRCConfig::Instance()->InitializeObstaclesFromConfig();
}

