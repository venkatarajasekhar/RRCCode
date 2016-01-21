#ifndef POSITION_H
#define POSITION_H

class Position {
  public:
    Position();
    Position(float x, float y);
    virtual ~Position();

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

  protected:
    float m_x;
    float m_y;
};

#endif // POSITION_H
