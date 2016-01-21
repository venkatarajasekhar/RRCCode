#include "RRCCore.h"
#include "RRCCommon/Area.h"
#include "Monitor/MonitorWrapper.h"
#include "Monitor/Monitor.h"

#include <RRCCommon/PositionFactory.h>
#include <RRCCommon/PositionType.h>

RRCCore* RRCCore::ms_instance = 0;

RRCCore* RRCCore::Instance() {
    if (ms_instance) {
        ms_instance = new RRCCore();
    }

    return ms_instance;
}

RRCCore::RRCCore() {

}

RRCCore::~RRCCore() {
    this->Release();
}

void RRCCore::Run() {
    Position *pos = PositionFactory::NewPosition(PositionType::Random);
    OnNewPointAdded(pos->x(), pos->y());
}

void RRCCore::OnNewPointAdded(float x, float y) {
    MonitorWrapper::Instance()->GetMonitor()->OnNewPointAdded(x, y);
}

void RRCCore::Release() {
    if (ms_instance) {
        delete ms_instance;
    }

    ms_instance = 0;
}

