#ifndef POSITIONFACTORY_H
#define POSITIONFACTORY_H

class Position;
enum PositionType;

class PositionFactory
{
public:
    static Position *NewPosition(PositionType posType);
};

#endif // POSITIONFACTORY_H
