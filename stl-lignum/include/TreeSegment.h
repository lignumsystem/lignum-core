#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>


namespace Lignum{

using namespace cxxadt;

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  METER L;                //Length of the tree segment
  KGC M;                  //Respiration of the tree segment during the time step
  LGMdouble omega;               //Gravelius order
  PA Pr;                  //Pressure
  LGMdouble fin;                 //Amount of water coming in
  LGMdouble fout;                //Amount of water going out
  METER R;                //Radius including bark
  METER Rtop;             //Radius at top
  METER Rh;               //Heartwood radius
  METER Rf;               //Radius to foliage limit
  KGC Wm;                 //Water mass of the tree segment 
  KGC Wf;                 //Foliage mass of the tree segment
  KGC Ws;                 //Sapwood mass of the tree segment
  KGC Wh;                 //Dry-weight (kg C) of heartwood
  list<METER> annual_rings; //Annual rings of the tree segment
};


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegment: public TreeCompartment<TS,BUD>{ 
  template <class TS1,class BUD1>
  friend list<METER> GetAnnualRings(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend KGC GetSapwoodMass(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const TreeSegment<TS1,BUD1>& ts, const LGMAD name);
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(TreeSegment<TS1,BUD1>& ts, const LGMAD name, const LGMdouble value);
public:
  TreeSegment();
  TreeSegment(const Point<METER>& p, const PositionVector& d, const LGMdouble go,
	      const METER l, const METER r, const METER rn, Tree<TS,BUD>* t);
  virtual ~TreeSegment();
  LGMdouble GetTranspiration(LGMdouble time);
  TreeSegmentAttributes& getTsa(){return tsa;}
  //  void photosynthesis();
private:
  TreeSegmentAttributes tsa;
};


}//close namespace Lignum

#include <TreeSegmentI.h>

#endif




