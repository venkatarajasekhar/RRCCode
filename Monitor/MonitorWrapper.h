#ifndef MONITORWRAPPER_H
#define MONITORWRAPPER_H

class Monitor;

class MonitorWrapper
{
public:
    MonitorWrapper(Monitor *monitor);
    virtual ~MonitorWrapper();
    static MonitorWrapper *Instance();
    Monitor *GetMonitor() const;

private:
    static MonitorWrapper *ms_instance;
    Monitor *monitor;
    void Release();
};

#endif // MONITORWRAPPER_H
