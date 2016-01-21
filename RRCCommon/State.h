#ifndef STATE_H
#define STATE_H

#include "Position.h"

class State {
  public:
    State();
    State(Position pos);
    ~State();

    Position getPos() const;
    void setPos(const Position &value);

protected:
    Position pos;
};

#endif // STATE_H
