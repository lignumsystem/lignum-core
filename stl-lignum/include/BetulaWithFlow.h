#ifndef BETULAWITHFLOW_HPP
#define BETULAWITHFLOW_HPP

#include <Tree.h>
//#include <BroadLeaf.h>
//#include <TreeSegmentFlow.h>

class BetulaWithFlow : public HwTreeSegment<BetulaWithFlow,DefaultBud<BetulaWithFlow> >
		       //		       public TreeSegmentFlow<BetulaWithFlow,DefaultBud<BetulaWithFlow> >
{
  
public:
  BetulaWithFlow(const cxxadt::Point<Lignum::METER>& p,const PositionVector& pv,
		 const LGMdouble go,const Lignum::METER l, const Lignum::METER r,
		 const Lignum::METER rn,
		 Lignum::Tree<BetulaWithFlow,DefaultBud<BetulaWithFlow> >* tree)
    :HwTreeSegment<BetulaWithFlow,DefaultBud<BetulaWithFlow> >(p,pv,go,l,r,rn,tree){}

  //     TreeSegmentFlow<BetulaWithFlow,DefaultBud<BetulaWithFlow> >(p,pv,go,l,r,rn,tree){}


};

#endif
