#ifndef RRCCORE_H
#define RRCCORE_H


class RRCCore
{
public:
    static RRCCore *Instance();
    static void Release();

    void Run();
    void OnNewPointAdded(float x, float y);

private:
    RRCCore();
    virtual ~RRCCore();
    static RRCCore *ms_instance;
};

#endif // RRCCORE_H
