#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <TreeCompartment.h>
#include <Axis.h>

template <class TS>
class BranchingPoint: public TreeCompartment<TS>{
  friend void InsertTerminatingBud(BranchingPoint<TS>& bp, Bud<TS>* bud);
  friend void InsertAxis(BranchingPoint<TS>& bp, Axis<TS>* axis);
  friend  list<Axis<TS>*>& GetAxisList(BranchingPoint<TS>& bp){return bp.axis_ls;}
public:
  BranchingPoint();
  BranchingPoint(const Point<METER>& p, const PositionVector& d, Tree<TS>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS>*> axis_ls;
};

#endif

