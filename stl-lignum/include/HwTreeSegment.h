#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>

#include <BroadLeaf.h>
#include <Uniform.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>


namespace Lignum{



template <class TS, class BUD=DefaultBud<TS>,class SHAPE=Ellipsis >
class HwTreeSegment:public TreeSegment<TS,BUD>
{
//#ifdef _MSC_VER   
/* 
	friend void InitializeForRadiation(HwTreeSegment<TS,BUD>& ts);
  friend int GetNumberOfLeaves(const HwTreeSegment<TS,BUD>& ts);
  friend LGMdouble SetLeafArea(HwTreeSegment<TS,BUD>& ts, const LGMdouble value);
  friend LGMdouble SetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value);
  friend LGMdouble GetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name);
  friend void DropLeaves(HwTreeSegment<TS,BUD>& ts);
*/
//#else
 
  template <class TS1,class BUD1, class S>
  friend void InsertLeaf(HwTreeSegment<TS1,BUD1,S>& ts, BroadLeaf<S>* l);

  template <class TS1,class BUD1,class S>
  friend void InitializeForRadiation(HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend int GetNumberOfLeaves(const HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend LGMdouble SetLeafArea(HwTreeSegment<TS1,BUD1,S>& ts, const LGMdouble value);

  template <class TS1,class BUD1,class S>
  friend LGMdouble SetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name, const LGMdouble value);

  template <class TS1,class BUD1,class S>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name);

  template <class TS1,class BUD1,class S>
  friend void DropLeaves(HwTreeSegment<TS1,BUD1,S>& ts);

//#endif
  template <class TS1,class BUD1, class S>
  friend std::list<BroadLeaf<S>*>& GetLeafList(HwTreeSegment<TS1,BUD1,S>& ts);

public:
  HwTreeSegment(const Point& p,const PositionVector& pv,
		const LGMdouble go, const METER l, const METER r,
		const METER rn,Tree<TS,BUD>* tree)
  :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){ SetValue(*this, vi, 1.0); }
  void photosynthesis();
  void respiration();
  virtual void createLeaves(vector<PositionVector>& petiole_directions,
			    METER pl,METER a,METER b);
protected:
  list<BroadLeaf<SHAPE>*> leaf_ls;
};





}//close namespace Lignum

#include <HwTreeSegmentI.h>
#include <HwTreeSegmentMetabolismI.h>


#endif
