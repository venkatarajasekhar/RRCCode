#ifndef Area_H
#define Area_H

#include "Position.h"

class Area : public Position
{
public:
    Area();
    Area(float x, float y, float width, float height);
    virtual ~Area();

    virtual float width() const;
    virtual void setWidth(float width);

    virtual float height() const;
    virtual void setHeight(float height);

private:
    float m_width;
    float m_height;
};

#endif // Area_H
