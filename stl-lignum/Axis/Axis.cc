
#include <Axis.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <numeric>


//default constructor
Axis::Axis()
{
  tree = NULL;
}

//Constructor, define position and direction in 3D space
//Also to access tree level parameters etc., set pointer
//to the tree this axis is part of
Axis::Axis(const Point<METER>& p, const PositionVector& d, Tree* t)
  :TreeCompartment(p,d,t)
{
}

Axis::~Axis()
{
  list<TreeCompartment*>::iterator first = tc_ls.begin();
  list<TreeCompartment*>::iterator last = tc_ls.end();

  while (first != last)
    delete *first++;
}

void Axis::Production()
{
  Prod p;
  for_each(tc_ls.begin(),tc_ls.end(),p);
}

TP Axis::GetProduction()
{
  GetProd gp;
  return accumulate(tc_ls.begin(),tc_ls.end(),0.0,gp);
}
