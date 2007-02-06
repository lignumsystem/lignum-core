#include "stdafx.h"
#include <BroadLeaf.h>

namespace Lignum{



  Petiole::Petiole(const Petiole& p)
    :begin(p.begin),end(p.end)
  {
  }

Petiole::Petiole(const Point& b, const Point& e)
  :begin(b),end(e)
{
}


Point GetStartPoint(const Petiole& p)
{
  return p.begin;
}

Point GetEndPoint(const Petiole& p)
{
  return p.end;
}

void SetStartPoint(Petiole& p, const Point& pnt)
{
  p.begin = pnt;
}
  
void SetEndPoint(Petiole& p, const Point& pnt)
{
  p.end = pnt;
}


PositionVector GetDirection(const Petiole& p)
{
  Point dp = p.end - p.begin;
  PositionVector d(dp.getX(),dp.getY(),dp.getZ()); //construct the vector
  d.normalize(); //normalize it

  return d;
}

}//closing namespace Lignum


