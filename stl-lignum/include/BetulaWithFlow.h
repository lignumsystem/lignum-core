#ifndef BETULAWITHFLOW_HPP
#define BETULAWITHFLOW_HPP

#include <Tree.h>
//#include <BroadLeaf.h>
//#include <TreeSegmentFlow.h>


namespace Lignum {

enum LGMBETULA { Nleaves, Aleaf } ;

class BetulaWithFlow : public HwTreeSegment<BetulaWithFlow,DefaultBud<BetulaWithFlow> >
		   
{
  friend LGMdouble GetValue(const BetulaWithFlow& ts, const LGMBETULA name);
  friend LGMdouble SetValue(BetulaWithFlow& ts, const LGMBETULA name, const LGMdouble value);

public:
  BetulaWithFlow(const cxxadt::Point<Lignum::METER>& p,const PositionVector& pv,
		 const LGMdouble go,const Lignum::METER l, const Lignum::METER r,
		 const Lignum::METER rn,
		 Lignum::Tree<BetulaWithFlow,DefaultBud<BetulaWithFlow> >* tree)
    :HwTreeSegment<BetulaWithFlow,DefaultBud<BetulaWithFlow> >(p,pv,go,l,r,rn,tree){}


 
  //private:
  int Nleaves;            //Number of leaves
  float Aleaf;            //Area of one leaf, common to all leaves in this TS

};

}
#include <BetulaWithFlowI.h>



#endif

