#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>

#include <LGMdecl.h>

#include <BroadLeaf.h>

namespace Lignum{

template <class TS,class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>{
  friend list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS,BUD>& ts);
public:
  HwTreeSegment(const Point<METER>& p,const PositionVector& pv,const TP go,const METER l,
		const METER r,const METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
private:
  list<BroadLeaf*> leaf_ls;
};

} //close namespace Lignum

#endif
