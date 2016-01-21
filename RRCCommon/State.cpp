#include "State.h"
#include "RRCCommon/PositionFactory.h"

State::State() {
    pos = *(PositionFactory::NewPosition(PositionType::Random));
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


