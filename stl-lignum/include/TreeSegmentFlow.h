#ifndef TREESEGMENTFLOW_HPP
#define TREESEGMENTFLOW_HPP

template <class TS,class BUD=DefaultBud<TS> >
class TreeSegmentFlow:public TreeSegment<TS,BUD>{
public:
  TreeSegmentFlow(const Point<METER>& p,const PositionVector& pv,const TP go,const METER l,
                const METER r,const METER rn,Tree<TS,BUD>* tree)
    :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree){}
};


#endif
