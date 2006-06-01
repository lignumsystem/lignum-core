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
  //Initiate omega and type to 0.0 and -1.0 respectively
  BranchingPoint(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  //Initiate type to -1.0
  BranchingPoint(const Point& p, const PositionVector& d, LGMdouble go,Tree<TS,BUD>* t);
  virtual ~BranchingPoint();
private:
  list<Axis<TS,BUD>*> axis_ls;
  LGMdouble maxd;//max diameter of the forking axes, see
		 //TreePhysiologyVigourIndex
  LGMdouble omega;//gravelius  order, if  not set  in lstringToLignum,
		  //set to 0.0, i.e. a meaningless value
  LGMdouble type;//type of  the bud  at the end  of axis,  initiate to
		 //-1.0, i.e. meaningless value
  LGMdouble state;//state of the  bud at the end of  axis: dead, alive
		  //dormant etc.
};


} //close namespace Lignum


#include <BranchingPointI.h>


#endif

