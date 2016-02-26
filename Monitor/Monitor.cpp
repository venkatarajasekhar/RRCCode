#include "Monitor.h"
#include <RRCCommon/Area.h>
#include <RRCCore/RRCCore.h>
#include <UI/UIModel.h>

//TODO: remove these two headers, this is just used as output new point position
#include <iostream>
#include <RRCCommon/Position.h>


Monitor::Monitor(UIModel *uiModel, RRCCore *rrcCore) : m_uiModel(uiModel), m_rrcCore(rrcCore)
{
}

Monitor::~Monitor() {

}

Area Monitor::GetSceneSize() const {
    return m_uiModel->GetSceneSize();
}

std::vector<Area> Monitor::GetObstacles() const
{
    return m_uiModel->GetObstacles();
}

void Monitor::OnButtonRunClicked()
{
    m_rrcCore->Run();
}

void Monitor::OnNewPointAdded(float x, float y)
{
    m_uiModel->OnNewPointAdded(x, y);
    std::cout << Position(x, y) << std::endl;
}
