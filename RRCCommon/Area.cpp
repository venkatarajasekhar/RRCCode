#include "Area.h"

Area::Area() : Position(0, 0)
{
    m_width = 0;
    m_height = 0;
}

Area::Area(float x, float y, float width, float height) : Position(x, y)
{
    m_width = width;
    m_height = height;
}

float Area::width() const
{
    return m_width;
}

void Area::setWidth(float width)
{
    m_width = width;
}
float Area::height() const
{
    return m_height;
}

void Area::setHeight(float height)
{
    m_height = height;
}



