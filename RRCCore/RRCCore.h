#ifndef RRCCORE_H
#define RRCCORE_H


class RRCCore
{
public:
    static RRCCore *Instance();
    void Run();
    void OnNewPointAdded(float x, float y);
    static void Release();

private:
    RRCCore();
    virtual ~RRCCore();
    static RRCCore *ms_instance;
};

#endif // RRCCORE_H
