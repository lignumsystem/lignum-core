
#include <BranchingPoint.h>
#include <TreeFunctor.h>
#include <algorithm>
#include <numeric>

template <class TS>
BranchingPoint<TS>::BranchingPoint()
{
  tree = NULL;
}

template <class TS>
BranchingPoint<TS>::BranchingPoint(const Point<METER>& p, const PositionVector& d,
				   Tree<TS>* t)
  :TreeCompartment<TS>(p,d,t)
{
}

template <class TS>
BranchingPoint<TS>::~BranchingPoint()
{
  list<Axis<TS>*>::iterator first = axis_ls.begin();
  list<Axis<TS>*>::iterator last = axis_ls.end();

  while (first != last){
    delete *first++;
  }
}

//create new axis and insert the bud into it
template <class TS>
void InsertTerminatingBud(BranchingPoint<TS>& bp, Bud<TS>* bud)
{
  Axis<TS> *axis = new Axis<TS>();
  
  InsertTreeCompartment(*axis,bud);
  bp.axis_ls.push_back(axis);
}

//insert the axis to the end of the list
template <class TS>
void InsertAxis(BranchingPoint<TS>& bp, Axis<TS>* axis)
{
  bp.axis_ls.push_back(axis);
}



