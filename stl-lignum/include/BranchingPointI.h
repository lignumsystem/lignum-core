#ifndef BRANCHINGPOINTI_H
#define BRANCHINGPOINTI_H

#include <list>
#include <algorithm>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <Bud.h>
#include <Tree.h>



namespace Lignum{


template <class TS,class BUD>
ostream &operator << (ostream& os, BranchingPoint<TS,BUD>& ts)
{	
	os << "DIRECTION " << GetDirection(ts);  
	os << "  POSITION " << GetPoint(ts);
	os << " END";

  return os;
}




template <class TS,class BUD>
BranchingPoint<TS,BUD>::BranchingPoint()
{
  tree = NULL;
  SetValue(*this, age, 0);
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::BranchingPoint(const Point& p, const PositionVector& d,
				       Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t)
{
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::~BranchingPoint()
{
  typename std::list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
  typename std::list<Axis<TS,BUD>*>::iterator last = axis_ls.end();

  while (first != last){
    delete *first++;
  }
}

// return the value of biggest radius of a segment forking away 
template <class TS,class BUD>
LGMdouble GetMaxRadius(BranchingPoint<TS,BUD>& bp)
{
  typename std::list<Axis<TS,BUD>*>::iterator first = GetAxisList(bp).begin();
  typename std::list<Axis<TS,BUD>*>::iterator last = GetAxisList(bp).end();

  LGMdouble max_rad = 0.0;
  while (first != last)
    {
      TreeSegment<TS,BUD> *ts = GetFirstTreeSegment(**first++);
      if (ts){
	if (GetValue(*ts, R) > max_rad)
	  max_rad = GetValue(*ts, R);
      }
    }
  return max_rad;
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

template <class TS,class BUD>
std::list<Axis<TS,BUD>*>& GetAxisList(BranchingPoint<TS,BUD>& bp)
{
  return bp.axis_ls;
}


}

#endif

