#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <Point.h>
#include <TreeCompartment.h>

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  YEAR age;               //Age of the tree segment
  METER L;                //Length of the tree segment
  KGC M;                  //Respiration of the tree segment during the time step
  TP omega;               //Gravelius order
  KGC P;                  //Photosythesis of the tree segment during the time step
  PA Pr;                  //Pressure
  TP fin;                 //Amount of water coming in
  TP fout;                //Amount of water going out
  MJ Qin;                 //Incoming radiation
  MJ Qabs;                //Absorbed radiation
  METER R;                //Radius including bark
  METER Rn;               //Heartwood radius
  METER Rf;               //Radius to foliage limit
  KGC Wm;                 //Water mass of the tree segment 
  KGC Wf;                 //Foliage mass of the tree segment
  KGC Ws;                 //Sapwood mass of the tree segment
  list<METER> annual_rings; //Annual rings of the tree segment
};


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegment: public TreeCompartment<TS,BUD>{ 
  friend list<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts);
  friend KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts);
  friend TP GetAttributeValue(const TreeSegment<TS,BUD>& ts, const TAD name);
  friend YEAR GetAttributeValue(const TreeSegment<TS,BUD>& ts, const TAI name);
  friend TP SetAttributeValue(TreeSegment<TS,BUD>& ts, const TAD name, const TP value);
  friend YEAR SetAttributeValue(TreeSegment<TS,BUD>& ts, const TAI name, 
				const YEAR  value);
public:
  TreeSegment();
  TreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
	      const METER l, const METER r, const METER rn, Tree<TS,BUD>* t);
  virtual ~TreeSegment();
  TP GetTranspiration(TP time);
  TreeSegmentAttributes& getTsa(){return tsa;}
private:
  TreeSegmentAttributes tsa;
};

#include <TreeSegmentI.h>

#endif




