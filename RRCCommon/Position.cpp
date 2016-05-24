#include "Position.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

Position::Position() : m_x(0), m_y(0) {

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

std::size_t Position::getDim() const
{
    return 2;
}

Position &Position::operator+=(const Position &rhs)
{
    m_x += rhs.x();
    m_y += rhs.y();
    return *this;
}

Position &Position::operator -=(const Position &rhs)
{
    m_x -= rhs.x();
    m_y -= rhs.y();
    return *this;
}

std::stringstream &operator<<(std::stringstream &ss, const Position &pos)
{
    ss << "[Position: - x: " << pos.x() << ", y: " << pos.y() << "]";
    return ss;
}

float Position::distToOtherPos(const Position &otherPos) const
{
    return sqrt(squaredDistToOtherPos(otherPos));
}

float Position::squaredDistToOtherPos(const Position &otherPos) const
{
    return pow(m_x - otherPos.x(), 2.0) + pow(m_y - otherPos.y(), 2.0);
}

float &Position::operator[](std::size_t n)
{
    switch(n){
    case 0:
        return m_x;
    case 1:
        return m_y;
    default:
        throw std::out_of_range("Exception thrown while accessing position element by operator [].");
    }
}

const float &Position::operator[](std::size_t n) const
{
    switch(n){
    case 0:
        return m_x;
    case 1:
        return m_y;
    default:
        throw std::out_of_range("Exception thrown while accessing position element by operator [].");
    }
}

std::ostream & operator <<(std::ostream &os, const Position &pos)
{
    std::stringstream ss;
    ss << pos;
    os << ss.str();
    return os;
}

Position operator+(const Position &lhs, const Position &rhs)
{
    Position sum = lhs;
    sum += rhs;
    return sum;
}

Position operator-(const Position &lhs, const Position &rhs)
{
    Position sum = lhs;
    sum -= rhs;
    return sum;
}

bool operator==(const Position &lhs, const Position &rhs)
{
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

bool operator!=(const Position &lhs, const Position &rhs)
{
    return !(lhs == rhs);
}



Position operator*(float x, const Position &rhs)
{
    Position newPos;
    newPos.setX(x * rhs.x());
    newPos.setY(x * rhs.y());

    return newPos;
}


Position operator*(const Position &lhs, float x)
{
    return x * lhs;
}
