#include "Range.h"

Range::Range() : m_min(Position(0, 0)), m_max(Position(0, 0)) {

}

Range::Range(const Position &min, const Position &max) : m_min(min), m_max(max) {

}
Position Range::min() const {
    return m_min;
}

void Range::setMin(const Position &min) {
    m_min = min;
}
Position Range::max() const {
    return m_max;
}

void Range::setMax(const Position &max) {
    m_max = max;
}

void Range::updateMin(const Position &newPos) {
    for(std::size_t i = 0; i < newPos.getDim(); ++i) {
        if(newPos[i] < m_min[i]) {
            m_min[i] = newPos[i];
        }
    }
}

void Range::updateMax(const Position &newPos) {
    for(std::size_t i = 0; i < newPos.getDim(); ++i) {
        if(newPos[i] > m_max[i]) {
            m_max[i] = newPos[i];
        }
    }
}

void Range::updateRange(const Position &newPos) {
    updateMin(newPos);
    updateMax(newPos);
}



