
#ifndef CFTREEFUNCTOR_H
#define CFTREEFUNCTOR_H


#include <Ellipsis.h>
#include <TreeCompartment.h>
#include <Algorithms.h>


namespace Lignum{


// This functor calculates the vigour values to segment with age=0
template <class TS,class BUD>
class CalculateVigours
{
public:
  CalculateVigours() { lastbp = NULL; }
  LGMdouble operator ()(LGMdouble& vig_val, TreeCompartment<TS,BUD>* tc)const;
  mutable BranchingPoint<TS,BUD>* lastbp;
  mutable LGMdouble max_area;
  mutable bool max_area_calculated;
  
};

}//namespace LIGNUM

#include <CfTreeFunctorI.h>

#endif
