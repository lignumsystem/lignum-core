#ifndef TREEMETABOLISMI_H
#define TREEMETABOLISMI_H

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


  //PHOTOSYBTHESIS


template <class TS,class BUD>
void Tree<TS,BUD>::photosynthesis()
{
  //Have TreeCompartments to do photosynthesis

  ForEach(*this, TreePhotosynthesis<TS,BUD>());
 

  //... and then SUM photosynthetic rates of all segments and update trees P

  LGMdouble initPh = 0.0;
  LGMdouble sumPh;
  sumPh = Accumulate(*this, initPh, SumTreePhotosynthesis<TS,BUD>());
  SetValue(*this, P, sumPh);

}


  //RESPIRATION


template <class TS,class BUD>
void Tree<TS,BUD>::respiration()
{
  //Have TreeCompartments to do photosynthesis

  ForEach(*this, TreeRespiration<TS,BUD>());


  //... and then SUM respiration rates of all segments and update tree M


LGMdouble initM = 0.0;
LGMdouble sumM;
sumM = Accumulate(*this, initM, SumTreeRespiration<TS,BUD>());
  SetValue(*this, M, sumM);

}


} //Closing namespace Lignum

#endif

 

























