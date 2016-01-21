#ifndef POSITIONFACTORY_H
#define POSITIONFACTORY_H

#include "PositionType.h"
class Position;

class PositionFactory
{
public:
    static Position *NewPosition(PositionType posType);
};

#endif // POSITIONFACTORY_H
