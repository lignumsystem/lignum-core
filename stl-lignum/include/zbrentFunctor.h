#ifndef ZBRENTFUNCTOR_H
#define ZBRENTFUNCTOR_H

#include <Tree.h>
#include <GCTree.h>
#include <fstream>
//#include <Algorithms.h>

namespace Lignum{

//Evaluate deltavariables before growth
template <class TS,class BUD>
class EvaluateDeltas: public AdaptableTCFunction<TS,BUD> 
{
public:
	TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
};



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



//Adjust other variables for evaluation of dry-weight after diameter growth
template <class TS,class BUD>
class DiameterGrowthBookkeep: public AdaptableTCFunction<TS,BUD> {
public:
TreeCompartment<TS,BUD>* operator()
  (TreeCompartment<TS,BUD>* tc)const;
};

//Collect dry weights of new parts & the increments below induced by them
template <class TS,class BUD>
class CollectDWAfterGrowth {
public:
  LGMdouble& operator()(LGMdouble& WSum, TreeCompartment<TS,BUD>* tc)const;
  CollectDWAfterGrowth() { lambda_zero = false; }
  bool lambda_zero;
};


template <class TS,class BUD>
class adjustSegmentSizeLambda: public AdaptableTCFunction<TS,BUD>{
public:
   TreeCompartment<TS,BUD>*operator ()(TreeCompartment<TS,BUD>* tc)const;
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





