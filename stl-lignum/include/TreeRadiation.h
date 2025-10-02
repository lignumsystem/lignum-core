/// \file TreeRadiation.h
/// \brief Obsolete 
#ifndef TREERADIATION_H
#define TREERADIATION_H


#include <string> 


namespace Lignum{


// WrapRadiationEvaluations takes care that the TreeCompartment is
// correctly instantaited for HwTreeSegment and CfTreeSegment (these
// two cases are wrapped into)
template <class F, class TS, class BUD>
class WrapRadiationEvaluations: public AdaptableTCFunction<TS,BUD> {
public:
  WrapRadiationEvaluations() {} //for hardwoods, no extinction
  //function required
  WrapRadiationEvaluations(std::string s); //conifers: extinction function
 //read from a file
  TreeCompartment<TS,BUD>* operator() (TreeCompartment<TS, BUD>* tc)const;
 private:
  F radiation_functor;
  ParametricCurve K; 
};


}

#include "TreeRadiationI.h"


#endif
































