/// \file BetulaWithFlow.h
/// \brief Experimental no longer active
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
  BetulaWithFlow(const cxxadt::Point& p,const PositionVector& pv,
		 const LGMdouble go,const METER l, const METER r,
		 const METER rn,
		 Tree<BetulaWithFlow,DefaultBud<BetulaWithFlow> >* tree)
    :HwTreeSegment<BetulaWithFlow,DefaultBud<BetulaWithFlow> >(p,pv,go,l,r,rn,tree){}


 
  //private:
  int Nleaves;            //Number of leaves
  float Aleaf;            //Area of one leaf, common to all leaves in this TS

};

} //closing namespace Lignum
#include <BetulaWithFlowI.h>



#endif

