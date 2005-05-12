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
  
  template <class TS1, class BUD1>
  friend LGMdouble GetValue(BranchingPoint<TS1,BUD1>& bp,LGMAD name);

  template <class TS1, class BUD1>
  friend LGMdouble SetValue(BranchingPoint<TS1,BUD1>& bp,LGMAD name, 
			    LGMdouble value); 
public:
  BranchingPoint();
  BranchingPoint(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS,BUD>*> axis_ls;
  LGMdouble maxd;
};


} //close namespace Lignum


#include <BranchingPointI.h>


#endif

