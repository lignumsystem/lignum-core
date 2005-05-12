#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <LGMSymbols.h>
#include <TreeCompartment.h>

using namespace cxxadt;

namespace Lignum{

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  KGC As0;                //Original sapwood area
  METER L;                //Length of the tree segment
  KGC M;                  //Respiration of the tree segment during the
			  //time step
  LGMdouble omega;        //Gravelius order
  METER R;                //Radius including bark
  METER Rtop;             //Radius at top
  METER Rh;               //Heartwood radius
  KGC Ws;                 //Sapwood mass of the tree segment
  KGC Wh;                 //Heartwood mass of the segment
  vector<METER> annual_rings; //Annual rings of the tree segment
  LGMdouble vigour;			//Vigour index
};


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegment: public TreeCompartment<TS,BUD>{
  template <class TS1,class BUD1>
  friend vector<METER> GetAnnualRings(const TreeSegment<TS1,BUD1>& ts);
   
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const TreeSegment<TS1,BUD1>& ts, const LGMAD name);
  
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(TreeSegment<TS1,BUD1>& ts, const LGMAD name, const LGMdouble value);
  
  template <class TS1,class BUD1>
  friend ostream &operator << (ostream& os, TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend istream &operator >> (istream& os, TreeSegment<TS1,BUD1>& ts);

  template <class TS1,class BUD1>
  friend KGC GetSapwoodMass(const TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend METER GetSapwoodArea(const TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend METER GetInitialSapwoodArea(const TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend METER SetRadius(TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend METER SetLastRing(TreeSegment<TS1,BUD1>& ts);
  
  template <class TS1,class BUD1>
  friend METER GetLastAnnualIncrement(const TreeSegment<TS1,BUD1>& ts);
  	
  template <class TS1,class BUD1>
  friend void AddNewRadiusToAnnualRings(TreeSegment<TS1,BUD1>& ts, LGMdouble radius);

  template <class TS1,class BUD1>
  friend Point GetPoint(const TreeSegment<TS1,BUD1>& ts,double fraction);

  template <class TS1,class BUD1>
  friend Point GetEndPoint(const TreeSegment<TS1,BUD1>& ts);
  template <class TS1,class BUD1>
  friend Point GetMidPoint(const TreeSegment<TS1,BUD1>& ts);
public:
  TreeSegment();
  TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
	      const METER l, const METER r, const METER rh, Tree<TS,BUD>* t);
  LGMdouble GetTranspiration(LGMdouble time);
  void SetYearCircles();
  TreeSegmentAttributes& getTsa(){return tsa;}
  
  void SetAnnualRings(std::vector<METER> rings);
  void SetAnnualGrowth(LGMdouble growth);
  METER AdjustAnnualGrowth(LGMdouble new_growth);
  int id;
  Point voxel_id;
  //  void photosynthesis();  OBS! TreeSegment does not have photosynthesis,
  //it is either CfTreeSegment or HwTreeSegment which handle it in their own ways	
private:
  TreeSegment<TS,BUD>& BendDown(RADIAN bending_angle);
  TreeSegmentAttributes tsa;
  
};


}//close namespace Lignum

#include "TreeSegmentI.h"


#endif




