#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <algorithm>
#include <numeric>
#include <Point.h>
#include <LGMdecl.h>


namespace Lignum{

using namespace cxxadt;

template <class TS,class BUD=DefaultBud<TS> >
class BranchingPoint: public TreeCompartment<TS,BUD>{
  template <class TS1,class BUD1>
  friend void InsertTerminatingBud(BranchingPoint<TS1,BUD1>& bp, Bud<TS1,BUD1>* bud);
  template <class TS1,class BUD1>
  friend void InsertAxis(BranchingPoint<TS1,BUD1>& bp, Axis<TS1,BUD1>* axis);
  template <class TS1,class BUD1>
  friend  list<Axis<TS1,BUD1>*>& GetAxisList(BranchingPoint<TS1,BUD1>& bp);
public:
  BranchingPoint();
  BranchingPoint(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS,BUD>*> axis_ls;
};

}//close namespace Lignum

#include <BranchingPointI.h>

#endif

