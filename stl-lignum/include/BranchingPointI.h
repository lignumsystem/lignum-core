#ifndef BRANCHING_POINTI_H
#define BRANCHING_POINTI_H

namespace Lignum{

template <class TS,class BUD>
BranchingPoint<TS,BUD>::BranchingPoint()
{
  tree = NULL;
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::BranchingPoint(const Point<METER>& p, const PositionVector& d,
				   Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::~BranchingPoint()
{
  list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
  list<Axis<TS,BUD>*>::iterator last = axis_ls.end();

  while (first != last){
    delete *first++;
  }
}

//create new axis and insert the bud into it
template <class TS,class BUD>
void InsertTerminatingBud(BranchingPoint<TS,BUD>& bp, Bud<TS,BUD>* bud)
{
  Axis<TS,BUD> *axis = new Axis<TS,BUD>();
  
  InsertTreeCompartment(*axis,bud);
  InsertAxis(bp,axis);
}

//insert the axis to the end of the list
template <class TS,class BUD>
void InsertAxis(BranchingPoint<TS,BUD>& bp, Axis<TS,BUD>* axis)
{
  bp.axis_ls.push_back(axis);
}

}//close namespace Lignum

#endif




