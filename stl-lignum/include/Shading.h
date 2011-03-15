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

//Is just like EvaluateRadiationForCfTreeSegment but uses instead of
//Firmaments diffuseRegionRadiationSum diffuseForestRegionRadiationSum,
//that is, the tree is surrounded by identical trees that are taken
//care with Lambert-Beer extinction.
//The tree level input parameters for diffuseForestRegionRadiationSum
//(needle area, extinction coefficient, tree height, height of
//crown base, stand density, and location of tree (for calculation of
// distance from tree stem)) are specified in the constructor.

template <class TS, class BUD>
class EvaluateRadiationForCfTreeSegmentForest {
public:
 EvaluateRadiationForCfTreeSegmentForest(const ParametricCurve& k, const LGMdouble& NA,
					 const LGMdouble& for_k, const LGMdouble& tree_h, const LGMdouble& Hcb,
					 const LGMdouble& dens, const Point& x0): K(k), needle_area(NA),
    forest_k(for_k), tree_height(tree_h), crownbase_height(Hcb),
    density(dens), stem_loc(x0) {}
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
private:
  const ParametricCurve& K;
  LGMdouble needle_area;
  LGMdouble forest_k;
  LGMdouble tree_height;
  LGMdouble crownbase_height;
  LGMdouble density;
  Point stem_loc;
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


//////////////////////////////////////////////////////////////////////////////////////////////
//Shading by woody parts only
//Two versions:
//1) ShadingEffectOfWoodyPartsSelf that can and should be used to check self-shading by
//woody parts: this takes the target_segment (in the constructor) and checks that comparison
//is not made itself as a shading TreeSegment. Consequently, the shading tree must be consisting of
//similar TreeSegments and Buds (<TS,BUD>) as the target one. Can thus be used for self-
//wood shading and wood-shading by other similar trees.
//2) ShadingEffectOfWoodyParts that takes a Point (e.g. Midpoint of a TreeSegment) in the
//constructor and makes comparisons for that. No checking is made (is not possible) whether the
//shading TreeSegment is the object (e.g. TreeSegment) for which evaluation is made. Can
//thus not be used to evaluate self wood shading in a tree.

//NOTE: Assumes that all trees have the same firmament, thus
//GetFirmamentWithMask(GetTree(*shaded_s) == GetFirmamentWithMask(GetTree(*ts))
/////////////////////////////////////////////////////////////////////////////////////////////


template <class TS,class BUD>
class ShadingEffectOfWoodyPartsSelf {
public:
  ShadingEffectOfWoodyPartsSelf(CfTreeSegment<TS,BUD>* ts, 
			       vector<double>& sectors)
    :shaded_s(ts), S(sectors){}
  //ForEach functor to compute shadiness
  TreeCompartment<TS,BUD>*  operator()(TreeCompartment<TS,BUD>* tc)const;
  //Get vector for S (shadiness) 
  vector<double>& getS(){return S;}
private:
  CfTreeSegment<TS,BUD>* shaded_s;
  vector<double>& S;
};

template <class TS,class BUD>
class ShadingEffectOfWoodyParts {
public:
  ShadingEffectOfWoodyParts(Point tl, 
			       vector<double>& sectors)
    :target_location(tl), S(sectors){}
  //ForEach functor to compute shadiness
  TreeCompartment<TS,BUD>*  operator()(TreeCompartment<TS,BUD>* tc)const;
  //Get vector for S (shadiness) 
  vector<double>& getS(){return S;}
private:
  Point target_location;
  vector<double>& S;
};


}     //END OF NAMESPACE LIGNUM


#include <ShadingI.h>

#endif















