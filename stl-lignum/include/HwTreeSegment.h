#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>
#include <Tree.h>


#include <BroadLeaf.h>
#include <Firmament.h>

namespace Lignum{

template <class TS, class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>{
  friend list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS,BUD>& ts);
  friend void InsertLeaf(HwTreeSegment<TS,BUD>& ts, BroadLeaf* l);
  friend void InitializeForRadiation(HwTreeSegment<TS,BUD>& ts);
  friend int GetNumberOfLeaves(const HwTreeSegment<TS,BUD>& ts);
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS,BUD>& ts);
  friend LGMdouble SetLeafArea(HwTreeSegment<TS,BUD>& ts, const LGMdouble value);
  friend LGMdouble GetValue(const HwTreeSegment<TS,BUD>& ts, const LGMAD name);
  

public:
  HwTreeSegment(const cxxadt::Point<METER>& p,const PositionVector& pv,
		const LGMdouble go,const Lignum::METER l, const Lignum::METER r,
		const Lignum::METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
private:
  list<BroadLeaf*> leaf_ls;
};

#include <HwTreeSegmentI.h>

} //close namespace Lignum



#endif
