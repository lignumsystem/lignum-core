#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <TreeCompartment.h>
#include <Axis.h>

class BranchingPoint: public TreeCompartment{
  friend Axis* GetFirstAxis();
  friend Axis* GetNextAxis();
  friend void InsertTerminatingBud(BranchingPoint& bp, Bud* bud);
public:
  BranchingPoint();
  BranchingPoint(const Point<METER>& p, const PositionVector& d, Tree* t);
  virtual ~BranchingPoint();
private:
  list<Axis*> axis_ls;
};

#endif

