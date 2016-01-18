#ifndef POSITION_H
#define POSITION_H

class Position {
  public:
    Position();
    Position(float x, float y);
    virtual ~Position();

    virtual float x() const;
    virtual void setX(float x);

    virtual float y() const;
    virtual void setY(float y);

  protected:
    float m_x;
    float m_y;
};

#endif // POSITION_H
