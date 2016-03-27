#include "State.h"
#include <sstream>

State::State() : m_pos(Position(0, 0)) {

}

State::State(const Position &pos) : m_pos(pos){
}

State::~State() {

}

Position State::getPos() const {
    return m_pos;
}

void State::setPos(const Position &value) {
    m_pos = value;
}

std::stringstream &operator<<(std::stringstream &ss, const State &state)
{
    ss << "[State: " << state.getPos() << "]";
    return ss;
}

std::ostream &operator<<(std::ostream &os, const State &state)
{
    std::stringstream ss;
    ss << state;
    os << ss.str();
    return os;
}


