
#include <TreeCompartment.h>
#include <stream.h>

template <class TS>
TreeCompartment<TS>::TreeCompartment()
{
}

template <class TS>
TreeCompartment<TS>::TreeCompartment(const Point<METER>& p, const PositionVector& d, 
				 Tree<TS>* t)
  :point(p),direction(d)
{
  tree = t;
}

template <class TS>
TreeCompartment<TS>::~TreeCompartment()
{
}


template <class TS>
Point<METER> GetPoint(const TreeCompartment<TS>& tc)
{
  return tc.point;
}

template <class TS>
PositionVector GetDirection(const TreeCompartment<TS>& tc)
{
  return  tc.direction;
}
