
#include <BranchingPoint.h>

BranchingPoint::BranchingPoint()
{
  tree = NULL;
}

BranchingPoint::BranchingPoint(const Point<METER>& p, const PositionVector& d,
			       Tree* t)
  :TreeCompartment(p,d,t)
{
}

BranchingPoint::~BranchingPoint()
{
  list<Axis*>::iterator first = axis_ls.begin();
  list<Axis*>::iterator last = axis_ls.end();

  while (first != last){
    delete *first++;
  }
}

