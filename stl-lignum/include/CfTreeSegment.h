#ifndef CFTREESEGMENT_HPP
#define CFTREESEGMENT_HPP

#include <Tree.h>

template <class TS,class BUD=DefaultBud<TS> >
class CfTreeSegment:public TreeSegment<TS,BUD>{
public:
  CfTreeSegment(const Point<METER>& p,const PositionVector& pv,const TP go,const METER l,
                const METER r,const METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
};

#endif
