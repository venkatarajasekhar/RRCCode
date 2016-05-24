#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position {
  public:
    Position();
    Position(float x, float y);
    ~Position();

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

    std::size_t getDim() const;

    float distToOtherPos(const Position &otherPos) const;
    float squaredDistToOtherPos(const Position &otherPos) const;

    Position& operator +=(const Position &rhs);
    Position& operator -=(const Position &rhs);

    friend std::ostream &operator <<(std::ostream &os, const Position &pos);
    friend std::stringstream &operator<<(std::stringstream &ss, const Position &pos);
    float &operator[](std::size_t n);
    const float &operator[](std::size_t n) const;

  protected:
    float m_x;
    float m_y;
};

// non-member overloaded operators
Position operator+(const Position &lhs, const Position &rhs);
Position operator-(const Position &lhs, const Position &rhs);
Position operator*(float x, const Position &rhs);
Position operator*(const Position &lhs, float x);
bool operator==(const Position &lhs, const Position &rhs);
bool operator!=(const Position &lhs, const Position &rhs);

#endif // POSITION_H
