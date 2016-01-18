#include "State.h"

State::State() {

}

State::State(Position pos) {
    this->pos = pos;
}

State::~State() {

}
Position State::getPos() const {
    return pos;
}

void State::setPos(const Position &value) {
    pos = value;
}

unsigned int State::GetStateDim() const
{
    return pos.GetDim();
}


