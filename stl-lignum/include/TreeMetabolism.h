#ifndef TREEMETABOLISM_H
#define TREEMETABOLISM_H

#include <Tree.h>


namespace Lignum{

template <class TS,class BUD>
class TreePhotosynthesis
{
public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
    tc->photosynthesis();
    return tc;
  }
};

template <class TS, class BUD>
class SumTreePhotosynthesis{
public:
  LGMdouble operator () (LGMdouble& cumPh, TreeCompartment<TS,BUD>* tc)const
  {
    if (CfTreeSegment<TS,BUD>* tts = dynamic_cast<CfTreeSegment<TS,BUD>*>(tc))
	{
      LGMdouble PP = GetValue(*tts, P);
      cumPh += PP;
    }
	else if (HwTreeSegment<TS,BUD>* tts = dynamic_cast<HwTreeSegment<TS,BUD>*>(tc))
	{
	  LGMdouble PP = GetValue(*tts, P);
      cumPh += PP;
	}
    return cumPh;
  }
};


template <class TS,class BUD>
  class TreeRespiration{
  public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
    tc->respiration();
    return tc;
  }
};

template <class TS, class BUD>
class SumTreeRespiration{
public:
  LGMdouble operator () (LGMdouble& cumM, TreeCompartment<TS,BUD>* tc)const
  {
    if (TreeSegment<TS,BUD>* tts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
      LGMdouble M_ts = GetValue(*tts, M);
      cumM += M_ts;
    }
    return cumM;
  }
};

}

#endif

 

























