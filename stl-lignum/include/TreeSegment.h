#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>

#include <TreeCompartment.h>

namespace Lignum{

using namespace cxxadt;

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  METER L;                //Length of the tree segment
  LGMdouble omega;               //Gravelius order
  METER R;                //Radius including bark
  METER Rtop;             //Radius at top
  METER Rh;               //Heartwood radius
  KGC P;                  //Amount of photosynthesis during time step (=rate of P.)
  KGC M;                  //Amount of respiration during time step (=rate of R.)
  list<METER> annual_rings; //Annual rings of the tree segment
};


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegment: public TreeCompartment<TS,BUD>{ 
  template <class TS1,class BUD1>
  friend list<METER> GetAnnualRings(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  Point GetEndPoint(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend KGC GetSapwoodMass(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const TreeSegment<TS1,BUD1>& ts, const LGMAD name);
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(TreeSegment<TS1,BUD1>& ts, const LGMAD name, const LGMdouble value);
public:
  TreeSegment();
  TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
	      const METER l, const METER r, const METER rn, Tree<TS,BUD>* t);
  virtual ~TreeSegment();
  LGMdouble GetTranspiration(LGMdouble time);
  TreeSegmentAttributes& getTsa(){return tsa;}
  // void photosynthesis();  OBS! TreeSegment does not have photosynthesis,
  //it is either CfTreeSegment or HwTreeSegment which handle it in their own ways
private:
  TreeSegmentAttributes tsa;
};


}//close namespace Lignum

#include <TreeSegmentI.h>

#endif




