#include "PositionFactory.h"
#include "PositionType.h"
#include "Position.h"
#include "PositionRandom.h"
#include "Monitor/Monitor.h"
#include "Monitor/MonitorWrapper.h"

Position* PositionFactory::NewPosition(PositionType posType)
{
    switch(posType)
    {
    case PositionType::Normal:
        return new Position();
    case PositionType::Random:
        return new PositionRandom(MonitorWrapper::Instance()->monitor->GetSceneSize());
    default:
        return 0;
    }
}
