
#include <Tree.h>

BudAttributes::BudAttributes()
  :ip(0.0),omega(0.0)
{
}

//default constructor
Bud::Bud()
{
  tree = NULL;
}

//Define position and direction in 3D space.
//Define gravelius order 
//Also to access tree level parameters etc., define
//the tree this bud is part of
Bud::Bud(const Point<METER>& p, const PositionVector& d, const TP go, 
	 Tree* t)
  :TreeCompartment(p,d,t)
{
  SetAttributeValue(*this,omega,go);
}

TreeSegment& Bud::createTreeSegment()const
{
  TreeSegment* ts = new TreeSegment();
  return (TreeSegment&) *ts;
}

Bud& Bud::createBud()const
{
  Bud* bud = new Bud();
  return (Bud&) *bud;
}

BranchingPoint& Bud::createBranchingPoint()const
{
  BranchingPoint* bp = new BranchingPoint();
  return (BranchingPoint&) *bp;
}
