#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <LGMdecl.h>


namespace Lignum{

using namespace cxxadt;

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  LGMdouble age;               //Age of the tree segment
  METER L;                //Length of the tree segment
  KGC M;                  //Respiration of the tree segment during the time step
  LGMdouble omega;               //Gravelius order
  KGC P;                  //Photosythesis of the tree segment during the time step
  PA Pr;                  //Pressure
  LGMdouble fin;                 //Amount of water coming in
  LGMdouble fout;                //Amount of water going out
  MJ Qin;                 //Incoming radiation
  MJ Qabs;                //Absorbed radiation
  METER R;                //Radius including bark
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
  friend list<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts);
  friend KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts);
  friend LGMdouble GetValue(const TreeSegment<TS,BUD>& ts, const LGMAD name);
  friend LGMdouble SetValue(TreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value);
public:
  TreeSegment();
  TreeSegment(const Point<METER>& p, const PositionVector& d, const LGMdouble go,
	      const METER l, const METER r, const METER rn, Tree<TS,BUD>* t);
  virtual ~TreeSegment();
  LGMdouble GetTranspiration(LGMdouble time);
  TreeSegmentAttributes& getTsa(){return tsa;}
private:
  TreeSegmentAttributes tsa;
};


}//close namespace Lignum

#include <TreeSegmentI.h>

#endif




