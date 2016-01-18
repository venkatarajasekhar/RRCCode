#include "MonitorWrapper.h"
#include "Monitor.h"

MonitorWrapper* MonitorWrapper::ms_instance = 0;

MonitorWrapper::MonitorWrapper(Monitor *monitor) {
    ms_instance = this;
    this->monitor = monitor;
}

MonitorWrapper::~MonitorWrapper() {
    this->Release();
}

MonitorWrapper *MonitorWrapper::Instance() {
    return ms_instance;
}

Monitor *MonitorWrapper::GetMonitor() const {
    return this->monitor;
}

void MonitorWrapper::Release() {
    if (ms_instance) {
        delete ms_instance;
    }

    ms_instance = 0;
}



