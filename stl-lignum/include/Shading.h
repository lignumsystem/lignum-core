#ifndef SHADING_H
#define SHADING_H

#include <Tree.h>

namespace Lignum {


//This functor EvaluateRadiationForHwTreeSegment evaluates shading
//caused by all other leaves to all leaves of this hardwood
//segment. This functor uses functor ShadingEffectOfLeaf<TS,BUD> to
//go through all leaves and to check the shading.

template <class TS, class BUD,class S= Ellipse>
class EvaluateRadiationForHwTreeSegment {
public:
  void operator()(TS* ts)const;
  void setExtinction(ParametricCurve& K); //not needed really for
 //hardwoods, included only to quarantee that program compiles also in
 //the case when constructor of WrapRadiationEvaluations<F,TS,BUD> is
 //invoked with sring argument for harrdwoods.
};

//This functor ShadingEffectOfLeaf<TS,BUD> evaluates shading caused
//by all leaves of a hardwood segment on a leaf (shaded_l) of a
//hardwood segment (shaded_s). 

template <class TS,class BUD,class S=Ellipse>
class ShadingEffectOfLeaf{
public:
  ShadingEffectOfLeaf(HwTreeSegment<TS,BUD,S>* ts, BroadLeaf<S>* lf);
  vector<LGMdouble>& operator()(vector<LGMdouble>& v,TreeCompartment<TS,BUD>* tc)const;

  HwTreeSegment<TS,BUD,S>* shaded_s;
  BroadLeaf<S>* shaded_l;
};


//This functor EvaluateRadiationForCfTreeSegment evaluates shading
//caused by all other segments on this conifer segment. This functor
//uses functor ShadingEffectOfCfTreeSegment<TS,BUD> to go through all
//segments to check the shading.

template <class TS, class BUD>
class EvaluateRadiationForCfTreeSegment {
public:
  EvaluateRadiationForCfTreeSegment(const ParametricCurve& k):K(k){}
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
private:
  const ParametricCurve& K;
};


//This functor ShadingEffectOfCfTreeSegment<TS,BUD> evaluates shading caused
//by a conifer segment on this conifer segment (shaded_s)

template <class TS,class BUD>
class ShadingEffectOfCfTreeSegment {
public:
  ShadingEffectOfCfTreeSegment(CfTreeSegment<TS,BUD>* ts, const ParametricCurve& K_in, 
			       vector<double>& sectors)
    :shaded_s(ts), K(K_in),S(sectors){}
  //ForEach functor to compute shadiness
  TreeCompartment<TS,BUD>*  operator()(TreeCompartment<TS,BUD>* tc)const;
  //Get vector for S (shadiness) 
  vector<double>& getS(){return S;}
private:
  CfTreeSegment<TS,BUD>* shaded_s;
  //Avoid unnecessary constructor calls in generic algorithms
  const ParametricCurve& K;
  vector<double>& S;
};



}     //END OF NAMESPACE LIGNUM


#include <ShadingI.h>

#endif















