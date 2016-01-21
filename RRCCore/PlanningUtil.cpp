#include "PlanningUtil.h"
#include <Monitor/MonitorWrapper.h>
#include <Monitor/Monitor.h>
#include <RRCCommon/Area.h>
#include <RRCCommon/Node.h>
#include <vector>

PlanningUtil::PlanningUtil()
{

}

PlanningUtil::~PlanningUtil()
{

}

bool PlanningUtil::IsCollision(Node *startNode, Node *endNode)
{
    std::vector<Area> obstacles = MonitorWrapper::Instance()->GetMonitor()->GetObstacles();
    for(std::size_t i = 0; i < obstacles.size(), ++i)
    {

    }
}

