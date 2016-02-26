#ifndef STATE_H
#define STATE_H

#include "Position.h"

/**
 * @brief The State class
 * State includes position, it may include other info, like orientation
 */
class State {
  public:
    State();
    State(Position pos);
    ~State();

    Position getPos() const;
    void setPos(const Position &value);

protected:
    Position m_pos;
};

#endif // STATE_H
