
#include <Axis.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <numeric>

template <class TS,class BUD>
Axis<TS,BUD>::~Axis()
{
  list<TreeCompartment<TS,BUD>*>::iterator first = tc_ls.begin();
  list<TreeCompartment<TS,BUD>*>::iterator last = tc_ls.end();

  while (first != last)
    delete *first++;
}

//default constructor
template <class TS,class BUD>
Axis<TS,BUD>::Axis()
{
  tree = NULL;
}

//Constructor, define position and direction in 3D space
//Also to access tree level parameters etc., set pointer
//to the tree this axis is part of
template <class TS,class BUD>
Axis<TS,BUD>::Axis(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t),tc_ls()
{
}


//insert a tree compartment to the last position of the list
template <class TS,class BUD>
void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* tc)
{
  axis.tc_ls.push_back(tc);
}

template <class TS,class BUD>
list<TreeCompartment<TS,BUD>*>&  GetTreeCompartmentList(Axis<TS,BUD>& axis)
{
  return  axis.tc_ls;
}

//Return the terminating bud of the axis
template <class TS,class BUD>
Bud<TS,BUD>* GetTerminatingBud(const Axis<TS,BUD>& axis)
{
  return (Bud<TS,BUD>*) axis.tc_ls.back();
}

