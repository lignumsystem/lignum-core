#ifndef BETULAWITHFLOW_HPP
#define BETULAWITHFLOW_HPP

#include <HwTreeSegment.h>
#include <TreeSegmentFlow.h>

class BetulaWithFlow : public HwTreeSegment<BetulaWithFlow>, 
		       public TreeSegmentFlow<BetulaWithFlow>
{
  BetulaWithFlow(const Point<METER>& p,const PositionVector& pv,const LGMdouble go,const METER l,
                const METER r,const METER rn,Tree<BetulaWithFlow>* tree)
    :HwTreeSegment<BetulaWithFlow>(p,pv,go,l,r,rn,tree), 
    TreeSegmentFlow<BetulaWithFlow>(p,pv,go,l,r,rn,tree){}

};

#endif
