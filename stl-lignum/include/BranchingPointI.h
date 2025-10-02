/// \file BranchingPointI.h
/// \brief Branching point implementation
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
BranchingPoint<TS,BUD>::BranchingPoint(const Point& p, const PositionVector& d,
				       Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t),maxd(0.0),omega(0.0),type(-1.0),state(ALIVE)
{
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::BranchingPoint(const Point& p, const PositionVector& d, LGMdouble go,
				       Tree<TS,BUD>* t)
  :TreeCompartment<TS,BUD>(p,d,t),maxd(0.0),omega(go),type(-1.0),state(ALIVE)
{
}

template <class TS,class BUD>
BranchingPoint<TS,BUD>::~BranchingPoint()
{
 
  typename list<Axis<TS,BUD>*>::iterator first = axis_ls.begin();
  //Delete axes, the list will be destroyed automatically.
  while (first != axis_ls.end()){
    delete *first++;
  }
}

template <class TS,class BUD>
double GetValue(BranchingPoint<TS,BUD>& bp, LGMAD name)
{
  if (name == LGAMaxD){//max diameter of the forking axes
    return bp.maxd;
  }
  else if (name == LGAage){//age
    return bp.tc_age;
  }
  else if (name == LGAomega){//gravelius order
    return bp.omega;
  }
  else if (name == LGAstate){//dead, alive, dormant etc.
    return bp.state;
  }
  else if (name == LGAtype){//dominant, nondominat etc.
    return bp.type;
  }
  else{
    cout << "GetValue in BP, unknown name: " << name << endl;
    return 0.0;
  }
}

template <class TS,class BUD>
double SetValue(BranchingPoint<TS,BUD>& bp, LGMAD name, LGMdouble value)
{
  LGMdouble old_value = GetValue(bp,name);
  if (name == LGAMaxD){    
    bp.maxd = value;
  }
  else if (name == LGAage){
    bp.tc_age = value;
  }
  else if (name == LGAomega){
    bp.omega = value;
  }
  else if (name == LGAstate){
    bp.state = value;
  }
  else if (name == LGAtype){
    bp.type = value;
  }
  return old_value;
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
	if (GetValue(*ts, LGAR) > max_rad)
	  max_rad = GetValue(*ts, LGAR);
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

