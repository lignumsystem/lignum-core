#ifndef MYTREESEGMENT_H
#define MYTREESEGMENT_H

#include <Tree.h>

class MyTreeSegment:public TreeSegment<MyTreeSegment>
{
  public:
  MyTreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
		const METER l, const METER r, const METER rn, 
		Tree<MyTreeSegment>* t);
};
#endif
