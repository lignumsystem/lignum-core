#ifndef HWTREESEGMENT_HPP
#define HWTREESEGMENT_HPP

#include <list>

#include <BroadLeaf.h>
#include <Uniform.h>
#include <LGMdecl.h>
#include <LGMUnits.h>
#include <LGMSymbols.h>
#include <Firmament.h>
#include <TreeSegment.h>
namespace Lignum{

template <class TS, class BUD=DefaultBud<TS>, class SHAPE=Ellipse>
class HwTreeSegment:public TreeSegment<TS,BUD>
{
 
  template <class TS1,class BUD1, class S>
  friend void InsertLeaf(HwTreeSegment<TS1,BUD1,S>& ts, BroadLeaf<S>* l);

  template <class TS1,class BUD1,class S>
  friend void InitializeForRadiation(HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend int GetNumberOfLeaves(const HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend LGMdouble GetLeafArea(const HwTreeSegment<TS1,BUD1,S>& ts);

  template <class TS1,class BUD1,class S>
  friend LGMdouble SetLeafArea(HwTreeSegment<TS1,BUD1,S>& ts, const LGMdouble value);

  template <class TS1,class BUD1,class S>
  friend LGMdouble SetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name, const LGMdouble value);

  template <class TS1,class BUD1,class S>
  friend LGMdouble GetValue(const HwTreeSegment<TS1,BUD1,S>& ts, const LGMAD name);


  template <class TS1,class BUD1, class S>
  friend std::list<BroadLeaf<S>*>& GetLeafList(HwTreeSegment<TS1,BUD1,S>& ts);

public:
  HwTreeSegment(const Point& p,const PositionVector& pv,
		const LGMdouble go, const METER l, const METER r,
		const METER rn,Tree<TS,BUD>* tree)
  :TreeSegment<TS,BUD>(p,pv,go,l,r,rn,tree)
  { //Initialize the vigor to -1.0, so  you for sure will see if it is
    //computed vor not.
    SetValue(*this, LGAvi,-1.0); 
  }
  void photosynthesis();
  void respiration();
  TcData& diameterGrowth(TcData& data);
  void aging();
  virtual void addLeaf(BroadLeaf<SHAPE>* l);
protected:
  list<BroadLeaf<SHAPE>*> leaf_ls;
};


}//close namespace Lignum

#include <HwTreeSegmentI.h>
#include <HwTreeSegmentMetabolismI.h>


#endif
