#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>

//#include <TreeSegment.h>
#include <BroadLeaf.h>
//#include <BetulaTortuosa.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>

//class BroadLeaf;


namespace Lignum{



template <class TS, class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>
{
#ifdef _MSC_VER   
  friend std::list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS,BUD>& ts);
  friend void InsertLeaf(HwTreeSegment<TS,BUD>& ts, BroadLeaf* l);
  friend void InitializeForRadiation(HwTreeSegment<TS,BUD>& ts);
  friend int GetNumberOfLeaves(const HwTreeSegment<TS,BUD>& ts);
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS,BUD>& ts);
  friend LGMdouble SetLeafArea(HwTreeSegment<TS,BUD>& ts, const LGMdouble value);
  friend LGMdouble SetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name, const LGMdouble value);
  friend LGMdouble GetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name);
  friend void DropLeaves(HwTreeSegment<TS,BUD>& ts);

#else
  template <class TS1,class BUD1>
  friend std::list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS1,BUD1>& ts);

  template <class TS1,class BUD1>
  friend void InsertLeaf(HwTreeSegment<TS1,BUD1>& ts, BroadLeaf* l);

  template <class TS1,class BUD1>
  friend void InitializeForRadiation(HwTreeSegment<TS1,BUD1>& ts);

  template <class TS1,class BUD1>
  friend int GetNumberOfLeaves(const HwTreeSegment<TS1,BUD1>& ts);

  template <class TS1,class BUD1>
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS1,BUD1>& ts);

  template <class TS1,class BUD1>
  friend LGMdouble SetLeafArea(HwTreeSegment<TS1,BUD1>& ts, const LGMdouble value);

  template <class TS1,class BUD1>
  friend LGMdouble SetValue(const HwTreeSegment<TS1,BUD1>& ts, const LGMAD name, const LGMdouble value);

  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1>& ts, const LGMAD name);

  template <class TS1,class BUD1>
  friend void DropLeaves(HwTreeSegment<TS1,BUD1>& ts);

#endif
public:
  HwTreeSegment(const Point& p,const PositionVector& pv,
		const LGMdouble go, const METER l, const METER r,
		const METER rn,Tree<TS,BUD>* tree)
		:TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){ SetValue(*this, vi, 1.0); }
  void photosynthesis();
  void respiration();
private:
	std::list<BroadLeaf*> leaf_ls;
};





}//close namespace Lignum

#include <HwTreeSegmentI.h>
#include <HwTreeSegmentMetabolismI.h>


#endif
