#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <TreeCompartment.h>
#include <Axis.h>

template <class TS>
class BranchingPoint: public TreeCompartment<TS>{
  friend Axis<TS>* GetFirstAxis();
  friend Axis<TS>* GetNextAxis();
  friend void InsertTerminatingBud(BranchingPoint<TS>& bp, Bud<TS>* bud);
public:
  BranchingPoint();
  BranchingPoint(const Point<METER>& p, const PositionVector& d, Tree<TS>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS>*> axis_ls;
};

#endif

