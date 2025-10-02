/// \file BetulaTortuosa.h
/// \brief Experimental Betula tortuosa no longer active
#ifndef BetulaTortuosa_HPP
#define BetulaTortuosa_HPP

#include <Tree.h>
#include <BroadLeaf.h>
#include <DefaultBud.h>
#include <HwTreeSegment.h>
#include <TreeSegmentFlow.h>




//template <class TS> class DefaultBud;

enum LGMBETULA { Nleaves, Aleaf } ;

namespace Lignum{

class BetulaTortuosa : public HwTreeSegment<BetulaTortuosa,DefaultBud<BetulaTortuosa> >
		   
{
  friend LGMdouble GetValue(const BetulaTortuosa& ts, const LGMBETULA name);
  friend LGMdouble SetValue(BetulaTortuosa& ts, const LGMBETULA name, const LGMdouble value);

public:
  BetulaTortuosa(const Point& p,const PositionVector& pv,
		 const LGMdouble go,const METER l, const METER r,
		 const METER rn,
		 Tree<BetulaTortuosa,DefaultBud<BetulaTortuosa> >* tree)
    :HwTreeSegment<BetulaTortuosa,DefaultBud<BetulaTortuosa> >(p,pv,go,l,r,rn,tree){}


 
  
  
  int Nleaves;            //Number of leaves
  float Aleaf;            //Area of one leaf, common to all leaves in this TS
  std::string data_info1;
  std::string data_info2;

  std::string leave_info;

  int id;
};


}

#endif

