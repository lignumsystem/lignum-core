#ifndef BRANCHINGPOINT_H
#define BRANCHINGPOINT_H

#include <list>
#include <algorithm>
#include <numeric>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>




using namespace cxxadt;

namespace Lignum{

template <class TS,class BUD=DefaultBud<TS> >
class BranchingPoint: public TreeCompartment<TS,BUD>{
#ifdef _MSC_VER   
  friend void InsertTerminatingBud(BranchingPoint<TS,BUD>& bp, Bud<TS,BUD>* bud); 
  friend void InsertAxis(BranchingPoint<TS,BUD>& bp, Axis<TS,BUD>* axis);
  friend ostream &operator << (ostream& os, BranchingPoint<TS,BUD>& ts);
  friend  std::list<Axis<TS,BUD>*>& GetAxisList(BranchingPoint<TS,BUD>& bp);

  friend LGMdouble GetMaxRadius(BranchingPoint<TS,BUD>& bp);

#else
  template <class TS1,class BUD1>
  friend void InsertTerminatingBud(BranchingPoint<TS1,BUD1>& bp, Bud<TS1,BUD1>* bud);
  template <class TS1,class BUD1>
  friend void InsertAxis(BranchingPoint<TS1,BUD1>& bp, Axis<TS1,BUD1>* axis);
  template <class TS1,class BUD1>
  friend ostream &operator << (ostream& os, BranchingPoint<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend std::list<Axis<TS1,BUD1>*>& GetAxisList(BranchingPoint<TS1,BUD1>& bp);

  template <class TS1, class BUD1>
  friend LGMdouble GetMaxRadius(BranchingPoint<TS1,BUD1>& bp);
#endif
public:
  BranchingPoint();
  BranchingPoint(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS,BUD>*> axis_ls;
};


} //close namespace Lignum


#include <BranchingPointI.h>


#endif

