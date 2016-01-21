#ifndef Area_H
#define Area_H

#include "Position.h"

class Area : public Position
{
public:
    Area();
    Area(float x, float y, float width, float height);
    ~Area();

    float width() const;
    void setWidth(float width);

    float height() const;
    void setHeight(float height);

    bool isInsideArea(Position pos);

private:
    float m_width;
    float m_height;
};

#endif // Area_H
