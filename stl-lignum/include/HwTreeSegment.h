#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>

#include <TreeSegment.h>
#include <BroadLeaf.h>
#include <Firmament.h>

namespace Lignum{
using namespace cxxadt;


template <class TS, class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>{
  template <class TS1,class BUD1>
  friend list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS1,BUD1>& ts);

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
  friend LGMdouble SetValue(const HwTreeSegment<TS1,BUD1>& ts, const LGMAD name,
			    const LGMdouble value);

  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1>& ts, const LGMAD name);
public:
  HwTreeSegment(const cxxadt::Point& p,const PositionVector& pv,
		const LGMdouble go, const METER l, const METER r,
		const METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
  void photosynthesis();
  void respiration();
private:
  list<BroadLeaf*> leaf_ls;
};

} //close namespace Lignum

#include <HwTreeSegmentI.h>
#include <HwTreeSegmentMetabolismI.h>





#endif








