#ifndef CFTREESEGMENT_H
#define CFTREESEGMENT_H

#include <list>
#include <mathsym.h>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <CfTreeFunctor.h>
#include <TreeSegment.h>

namespace Lignum{

using namespace cxxadt;

class CfTreeSegmentAttributes{
public:
  CfTreeSegmentAttributes();
  LGMdouble P;            //Amount of photosynthesis (kg C) during time step
  LGMdouble Qin;          //Irradiance of incoming radiation (MJ/m2)
  LGMdouble Qabs;          //Amount of absorbed radiation (MJ) (during time step)
  METER Rf;               //Radius to foliage limit
  KGC Wf;                 //Foliage mass of the tree segment
  LGMdouble sf;           //Specific foliage area (=foliage area(total)/weight)
};


template <class TS,class BUD=DefaultBud<TS> >
class CfTreeSegment:public TreeSegment<TS,BUD>{
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(const CfTreeSegment<TS1,BUD1>& ts, const LGMAD name);
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(CfTreeSegment<TS1,BUD1>& ts, const LGMAD name,
			    const LGMdouble);
public:
  CfTreeSegment(const Point& p,const PositionVector& pv,const LGMdouble go,const METER l,
                const METER r,const METER rn,Tree<TS,BUD>* tree);
  void photosynthesis();
  void respiration();
private:
  CfTreeSegmentAttributes cftsa;
};


}//close namespace Lignum

#include <CfTreeSegmentI.h>
#include <CfTreeSegmentMetabolismI.h>


#endif



