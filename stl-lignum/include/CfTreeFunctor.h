/// \file CfTreeFunctor.h
/// \brief Functors for generic algorithms  
#ifndef CFTREEFUNCTOR_H
#define CFTREEFUNCTOR_H


#include <Ellipsis.h>
#include <TreeCompartment.h>
#include <Algorithms.h>


namespace Lignum{


///\brief Calculate the vigour values.
///\deprecated Not implemented
template <class TS,class BUD>
class CalculateVigours
{
public:
  CalculateVigours() { lastbp = NULL; }
  ///\brief Calculate the vigour values.
  ///\param vig_val Vigour value
  ///\param tc Tree segment
  ///\return Vigour value calculated
  ///\pre Segment age = 0
  LGMdouble operator ()(LGMdouble& vig_val, TreeCompartment<TS,BUD>* tc)const;
  mutable BranchingPoint<TS,BUD>* lastbp;
  mutable LGMdouble max_area;///< Max area of segments connected the branching point in front of \p tc
  mutable bool max_area_calculated;///< The \p max_area calculated
  
};

}//namespace LIGNUM

#include <CfTreeFunctorI.h>

#endif
