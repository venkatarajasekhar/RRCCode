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
    State(const Position &pos);
    ~State();

    Position getPos() const;
    void setPos(const Position &value);

    friend std::ostream &operator<<(std::ostream &os, const State &state);
protected:
    friend std::stringstream &operator<<(std::stringstream &ss, const State &state);
    Position m_pos;
};

#endif // STATE_H
