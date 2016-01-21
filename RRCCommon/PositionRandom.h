#ifndef POSITIONRANDOM_H
#define POSITIONRANDOM_H

#include "Position.h"
class Area;

class PositionRandom : public Position
{
public:
    PositionRandom(Area area);
    ~PositionRandom();
};

#endif // POSITIONRANDOM_H
