#ifndef TREESEGMENTFLOW_HPP
#define TREESEGMENTFLOW_HPP




#include <Tree.h>

namespace Lignum{

template <class TS,class BUD=DefaultBud<TS> >
class TreeSegmentFlow:public TreeSegment<TS,BUD>{
public:

  TreeSegmentFlow(const Point& p,const PositionVector& pv,
		  const LGMdouble go,const METER l,const METER r,
		  const METER rn,Tree<TS,BUD>* tree)

    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
};


}

#endif
