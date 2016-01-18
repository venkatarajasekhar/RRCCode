#ifndef STATE_H
#define STATE_H

#include "Position.h"

class State {
  public:
    State();
    State(Position pos);
    virtual ~State();

    virtual Position getPos() const;
    virtual void setPos(const Position &value);
    virtual unsigned int GetStateDim() const;

protected:
    Position pos;
};

#endif // STATE_H
