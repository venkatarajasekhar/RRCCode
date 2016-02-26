#ifndef RANGE_H
#define RANGE_H

#include "RRCCommon/Position.h"

class Range
{
public:
    Range();
    Range(const Position &min, const Position &max);
    Position min() const;
    void setMin(const Position &min);

    Position max() const;
    void setMax(const Position &max);

    void updateMin(const Position &newPos);
    void updateMax(const Position &newPos);
    void updateRange(const Position &newPos);

private:
    Position m_min;
    Position m_max;
};

#endif // RANGE_H
