#ifndef TREESEGMENTFLOW_HPP
#define TREESEGMENTFLOW_HPP




#include <Tree.h>


template <class TS,class BUD=DefaultBud<TS> >
class TreeSegmentFlow:public TreeSegment<TS,BUD>{
public:

  TreeSegmentFlow(const cxxadt::Point<Lignum::METER>& p,const PositionVector& pv,
		  const LGMdouble go,const Lignum::METER l,const Lignum::METER r,
		  const Lignum::METER rn,Lignum::Tree<TS,BUD>* tree)

    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
};


#endif
