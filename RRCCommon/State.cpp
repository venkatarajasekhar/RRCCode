#include "State.h"

State::State() : m_pos(Position(0, 0)) {

}

State::State(Position pos) : m_pos(pos){
}

State::~State() {

}

Position State::getPos() const {
    return m_pos;
}

void State::setPos(const Position &value) {
    m_pos = value;
}


