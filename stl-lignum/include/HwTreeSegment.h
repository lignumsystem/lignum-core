#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP
#include <list>
#include <Tree.h>

#include <BroadLeaf.h>

namespace Lignum{

template <class TS,class BUD=DefaultBud<TS> >
class HwTreeSegment:public TreeSegment<TS,BUD>{
  friend list<BroadLeaf*>& GetLeafList(HwTreeSegment<TS,BUD>& ts);
public:
  HwTreeSegment(const cxxadt::Point<METER>& p,const PositionVector& pv,
		const LGMdouble go,const Lignum::METER l, const Lignum::METER r,
		const Lignum::METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
private:
  list<BroadLeaf*> leaf_ls;
};

} //close namespace Lignum

#endif
