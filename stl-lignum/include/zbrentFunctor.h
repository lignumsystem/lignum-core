#ifndef ZBRENTFUNCTOR_H
#define ZBRENTFUNCTOR_H

#include <Tree.h>
//#include <Algorithms.h>

namespace Lignum{




//Accumulate down diameter growth
template <class TS,class BUD>
class SetNewRing
{
public:
  LGMdouble& operator()(LGMdouble& As, TreeCompartment<TS,BUD>* tc)const;
};


//Accumulate down diameter growth
template <class TS,class BUD>
class AdjustDiameterHwGrowth
{
public:
  LGMdouble& operator()(LGMdouble& As, TreeCompartment<TS,BUD>* tc)const;
};


//Accumulate down diameter growth
template <class TS,class BUD>
class AdjustDiameterCfGrowth
{
public:
  LGMdouble& operator()(LGMdouble& As, TreeCompartment<TS,BUD>* tc)const;
};




//Collect dry weights of new parts & the increments below induced by them
template <class TS,class BUD>
class CollectCfDWAfterGrowth {
public:
  LGMdouble& operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const;
  CollectCfDWAfterGrowth() { lambda_zero = false; }
  bool lambda_zero;
};



//Collect dry weights of new parts & the increments below induced by them
template <class TS,class BUD>
class CollectDWAfterGrowth {
public:
  LGMdouble& operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const;
  CollectHwDWAfterGrowth() { lambda_zero = false; }
  bool lambda_zero;
};

template <class TS,class BUD>
class adjustSegmentSizeLambda: public AdaptableTCFunction<TS,BUD>{
public:
   TreeCompartment<TS,BUD>*
   operator ()(TreeCompartment<TS,BUD>* tc)const;
   LGMdouble rel_lambda;
};


template <class TS,class BUD>
class BookkeepAfterZbrent: public AdaptableTCFunction<TS,BUD>{
public:
   TreeCompartment<TS,BUD>*
   operator ()(TreeCompartment<TS,BUD>* tc)const;
};


}

#include "zbrentFunctorI.h"

#endif





