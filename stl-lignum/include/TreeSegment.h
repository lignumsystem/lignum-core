#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <LGMSymbols.h>
#include <LGMUnits.h>
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
  MJ Qin;                 //Incoming radiation
  MJ Qabs;                //Absorbed radiation
  METER R;                //Radius including bark
  METER Rn;               //Heartwood radius
  METER Rf;               //Radius to foliage limit
  KGC Wf;                 //Foliage mass of the tree segment
  KGC Ws;                 //Sapwood mass of the tree segment
  list<METER> annual_rings; //Annual rings of the tree segment
};

class TreeSegment: public TreeCompartment{ 
  friend list<METER> GetAnnualRings(const TreeSegment& ts);
  friend KGC GetSapwoodMass(const TreeSegment& ts);
  friend TP GetAttributeValue(const TreeSegment& ts, const TAD name);
  friend YEAR GetAttributeValue(const TreeSegment& ts, const TAI name);
  template <class T1,class T2>
  friend T2 SetAttributeValue(TreeSegment& ts, const T1 name, const T2 value);
public:
  TreeSegment();
  TreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
	      const METER l, const METER r, const METER rn, Tree* t);
  virtual ~TreeSegment();
private:
  TreeSegmentAttributes tsa;
};

#endif

