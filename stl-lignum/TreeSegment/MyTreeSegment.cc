#include <MyTreeSegment.h>

MyTreeSegment::MyTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
			     const METER l, const METER r, const METER rn, 
			     Tree<MyTreeSegment>* t)
  :TreeSegment<MyTreeSegment>(p,d,go,l,r,rn,t)
{
}
