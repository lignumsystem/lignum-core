
#include <BranchingPoint.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <numeric>

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

void BranchingPoint::Production()
{
  Prod p;
  for_each(axis_ls.begin(),axis_ls.end(),p);
}

TP BranchingPoint::GetProduction()
{
  GetProd gp;
  return accumulate(axis_ls.begin(),axis_ls.end(),0.0,gp);
}
