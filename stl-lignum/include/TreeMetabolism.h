#ifndef TREEMETABOLISM_H
#define TREEMETABOLISM_H

namespace Lignum{

  //Classes for calculation of photosynthesis and respiration

template <class TS,class BUD>
  class TreePhotosynthesis{
  public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const{
    tc->photosynthesis();
    return tc;
  }
};

template <class TS, class BUD>
class SumTreePhotosynthesis{
public:
  LGMdouble operator () (LGMdouble& cumPh, 
			 TreeCompartment<TS,BUD>* tc)const{
    if (TS* tsc = dynamic_cast<TS*>(tc)) {
      LGMdouble PP = GetValue(*tsc, P);
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
  LGMdouble operator () (LGMdouble& cumM, 
			 TreeCompartment<TS,BUD>* tc)const{
    if (TS* tsc = dynamic_cast<TS*>(tc)) {
      LGMdouble M_ts = GetValue(*tsc, M);
      cumM += M_ts;
    }
    return cumM;
  }
};


} //Closing namespace Lignum

#endif

 

























