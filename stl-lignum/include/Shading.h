#ifndef SHADING_H
#define SHADING_H

#include <Tree.h>

namespace Lignum {


//This functor EvaluateRadiationForHwTreeSegment evaluates shading
//caused by all other leaves to all leaves of this hardwood
//segment. This functor uses functor ShadingEffectOfLeaf<TS,BUD> to
//go through all leaves and to check the shading.

template <class TS, class BUD>
class EvaluateRadiationForHwTreeSegment {
public:
  void operator()(TreeSegment<TS,BUD>* ts)const;
  void setExtinction(ParametricCurve& K); //not needed really for
 //hardwoods, included only to quarantee that program compiles also in
 //the case when constructor of WrapRadiationEvaluations<F,TS,BUD> is
 //invoked with sring argument for harrdwoods.
};

//This functor ShadingEffectOfLeaf<TS,BUD> evaluates shading caused
//by all leaves of a hardwood segment on a leaf (shaded_l) of a
//hardwood segment (shaded_s). 

template <class TS,class BUD>
class ShadingEffectOfLeaf{
public:
  ShadingEffectOfLeaf(HwTreeSegment<TS,BUD>* ts, BroadLeaf* lf);
  vector<LGMdouble>& operator()(vector<LGMdouble>& v,TreeCompartment<TS,BUD>* tc)const;

  HwTreeSegment<TS,BUD>* shaded_s;
  BroadLeaf* shaded_l;
};


//This functor EvaluateRadiationForCfTreeSegment evaluates shading
//caused by all other segments on this conifer segment. This functor
//uses functor ShadingEffectOfCfTreeSegment<TS,BUD> to go through all
//segments to check the shading.

template <class TS, class BUD>
class EvaluateRadiationForCfTreeSegment {
public:
  void  operator()(TreeSegment<TS,BUD>* ts)const;
  void setExtinction(ParametricCurve& K);
private:
  ParametricCurve K;
};


//This functor ShadingEffectOfCfTreeSegment<TS,BUD> evaluates shading caused
//by a conifer segment on this conifer segment (shaded_s)

template <class TS,class BUD>
class ShadingEffectOfCfTreeSegment {
public:
  ShadingEffectOfCfTreeSegment(CfTreeSegment<TS,BUD>* ts, const ParametricCurve& K_in) {
    shaded_s = ts;
    K = K_in;
  }
  vector<LGMdouble>& operator()(vector<LGMdouble>& v,TreeCompartment<TS,BUD>* tc)const;
private:
  CfTreeSegment<TS,BUD>* shaded_s;
  ParametricCurve K;
};



}     //END OF NAMESPACE LIGNUM


#include <ShadingI.h>

#endif















