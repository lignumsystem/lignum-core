#ifndef CFTREESEGMENT_HPP
#define CFTREESEGMENT_HPP

#include <LGMdecl.h>

namespace Lignum{

template <class TS,class BUD=DefaultBud<TS> >
class CfTreeSegment:public TreeSegment<TS,BUD>{
public:
  CfTreeSegment(const Point<METER>& p,const PositionVector& pv,const LGMdouble go,const METER l,
                const METER r,const METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
};

}//close namespace Lignum
#endif
