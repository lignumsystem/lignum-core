
#include <Axis.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <numeric>

template <class TS>
Axis<TS>::~Axis()
{
  list<TreeCompartment<TS>*>::iterator first = tc_ls.begin();
  list<TreeCompartment<TS>*>::iterator last = tc_ls.end();

  while (first != last)
    delete *first++;
}

//default constructor
template <class TS>
Axis<TS>::Axis()
{
  tree = NULL;
}

//Constructor, define position and direction in 3D space
//Also to access tree level parameters etc., set pointer
//to the tree this axis is part of
template <class TS>
Axis<TS>::Axis(const Point<METER>& p, const PositionVector& d, Tree<TS>* t)
  :TreeCompartment<TS>(p,d,t),tc_ls()
{
}


//insert a tree compartment to the last position of the list
template <class TS>
void InsertTreeCompartment(Axis<TS>& axis, TreeCompartment<TS>* tc)
{
  axis.tc_ls.push_back(tc);
}

template <class TS>
list<TreeCompartment<TS>*>&  GetTreeCompartmentList(Axis<TS>& axis)
{
  return  axis.tc_ls;
}

//Return the terminating bud of the axis
template <class TS>
Bud<TS>* GetTerminatingBud(const Axis<TS>& axis)
{
  return (Bud<TS>*) axis.tc_ls.back();
}

