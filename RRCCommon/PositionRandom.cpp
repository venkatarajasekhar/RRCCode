#include "PositionRandom.h"
#include <stdlib.h>
#include "Area.h"

PositionRandom::PositionRandom(Area area)
{
   m_x = area.x() + area.width() * (((float)rand()) / RAND_MAX);
   m_y = area.y() + area.height() * (((float)rand()) / RAND_MAX);
}

PositionRandom::~PositionRandom()
{

}

