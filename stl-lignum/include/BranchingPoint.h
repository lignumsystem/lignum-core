#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <algorithm>
#include <numeric>
#include <TreeFunctor.h>
#include <TreeCompartment.h>

template <class TS,class BUD=DefaultBud<TS> >
class BranchingPoint: public TreeCompartment<TS,BUD>{
  friend void InsertTerminatingBud(BranchingPoint<TS,BUD>& bp, Bud<TS,BUD>* bud);
  friend void InsertAxis(BranchingPoint<TS,BUD>& bp, Axis<TS,BUD>* axis);
  friend  list<Axis<TS,BUD>*>& GetAxisList(BranchingPoint<TS,BUD>& bp){return bp.axis_ls;}
public:
  BranchingPoint();
  BranchingPoint(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS,BUD>*> axis_ls;
};

#include <BranchingPointI.h>

#endif

