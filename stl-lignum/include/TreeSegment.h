#ifndef TREESEGMENT_H
#define TREESEGMENT_H

#include <list>
#include <iostream>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <LGMSymbols.h>
#include <TreeSegmentWithFlow.h>
#include <TreeCompartment.h>



#ifdef _MSC_VER
extern int num_of_leaves;
extern bool clean_save;
#endif

using namespace cxxadt;

namespace Lignum{

class TreeSegmentAttributes{
public:
  TreeSegmentAttributes();
  METER L;                //Length of the tree segment
  KGC M;                  //Respiration of the tree segment during the time step
  LGMdouble omega;        //Gravelius order
  METER R;                //Radius including bark
  METER Rtop;             //Radius at top
  METER Rh;               //Heartwood radius
 // KGC Wf;                 //Foliage mass of the tree segment
  KGC Ws;                 //Sapwood mass of the tree segment
  KGC Wh;                 //Dry-weight (kg C) of heartwood
  std::vector<METER> annual_rings; //Annual rings of the tree segment
  LGMdouble vigour;			//Vigour index
};


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegment: public TreeCompartment<TS,BUD>{
#ifdef _MSC_VER
  friend std::vector<METER> GetAnnualRings(const TreeSegment<TS,BUD>& ts);  
  friend KGC GetSapwoodMass(const TreeSegment<TS,BUD>& ts);
  friend METER GetSapwoodArea(const TreeSegment<TS,BUD>& ts);
  friend METER GetInitialSapwoodArea(const TreeSegment<TS,BUD>& ts);
  friend METER SetRadius(TreeSegment<TS,BUD>& ts);
  friend METER SetLastRing(TreeSegment<TS,BUD>& ts);
  friend METER GetLastAnnualIncrement(const TreeSegment<TS,BUD>& ts);
  friend LGMdouble GetValue(const TreeSegment<TS,BUD>& ts, const LGMAD name);
  friend LGMdouble SetValue(TreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value);
  friend void AddNewRadiusToAnnualRings(TreeSegment<TS,BUD>& ts, LGMdouble radius);

  friend ostream &operator << (ostream& os, TreeSegment<TS,BUD>& ts);
  friend istream &operator >> (istream& os, TreeSegment<TS,BUD>& ts);

#else
  template <class TS1,class BUD1>
  friend std::vector<METER> GetAnnualRings(const TreeSegment<TS1,BUD1>& ts);
   
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

#endif
  template <class TS1,class BUD1>
  Point GetEndPoint(const TreeSegment<TS1,BUD1>& ts);

public:
  TreeSegment();
  TreeSegment(const Point& p, const PositionVector& d, const LGMdouble go,
	      const METER l, const METER r, const METER rn, Tree<TS,BUD>* t);
  virtual ~TreeSegment();
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




