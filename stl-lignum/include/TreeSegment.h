#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <Point.h>
#include <TreeCompartment.h>

template<class TS>
TP GetTreeParameterValue(const Tree<TS>& tree, const TPD name);

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
  KGC Wm;                  //Water mass of the tree segment 
  KGC Wf;                 //Foliage mass of the tree segment
  KGC Ws;                 //Sapwood mass of the tree segment
  list<METER> annual_rings; //Annual rings of the tree segment
};


template <class TS>
class TreeSegment: public TreeCompartment<TS>{ 
  friend list<METER> GetAnnualRings(const TreeSegment<TS>& ts);
  friend KGC GetSapwoodMass(const TreeSegment<TS>& ts);
  friend TP GetTSAttributeValue(const TreeSegment<TS>& ts, const TAD name);
  friend YEAR GetTSAttributeValue(const TreeSegment<TS>& ts, const TAI name);
  friend TP SetTSAttributeValue(TreeSegment<TS>& ts, const TAD name, const TP value);
  friend YEAR SetTSAttributeValue(TreeSegment<TS>& ts, const TAI name, 
				  const YEAR  value);
public:
  TreeSegment();
  TreeSegment(const Point<METER>& p, const PositionVector& d, const TP go,
	      const METER l, const METER r, const METER rn, Tree<TS>* t);
  virtual ~TreeSegment();
  TP GetTranspiration(TP time);

private:
  TreeSegmentAttributes tsa;
};


#endif




