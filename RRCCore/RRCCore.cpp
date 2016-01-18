#include "RRCCore.h"
#include "RandomNode.h"
#include "RRCCommon/Area.h"
#include "Monitor/MonitorWrapper.h"
#include "Monitor/Monitor.h"

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
    Area worldSize = MonitorWrapper::Instance()->GetMonitor()->GetSceneSize();
    RandomNode newPoint(worldSize.GetNthDimLimit(1), worldSize.GetNthDimLimit(2));
    OnNewPointAdded(newPoint.GetX(), newPoint.GetY());
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

