#include "Position.h"

Position::Position()
{
   m_x = 0;
   m_y = 0;
}

Position::Position(float x, float y) : m_x(x), m_y(y) {

}

Position::~Position() {

}
float Position::x() const
{
    return m_x;
}

void Position::setX(float x)
{
    m_x = x;
}
float Position::y() const
{
    return m_y;
}

void Position::setY(float y)
{
    m_y = y;
}
