#include <TreeCompartment.h>

Point<METER> GetPoint(const TreeCompartment& tc)
{
  return tc.point;
}

PositionVector GetDirection(const TreeCompartment& tc)
{
  return  tc.direction;
}
