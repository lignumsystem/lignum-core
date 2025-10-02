/// \file Shading.h
/// \brief Light attenuation calculations
///
///Light attenuation calculations for hardwood species and conifers.
///The functors are based on parwise comparison of the shading elements.
///The algorithmic complexities are \f$ \mathcal{O}(n^2) \f$.
#ifndef SHADING_H
#define SHADING_H

#include <Tree.h>

namespace Lignum {

///\brief Hardwood radiation climate
///
///Evaluate shading aused by all other leaves to all leaves of this hardwood
///segment. This functor uses functor ShadingEffectOfLeaf to
///go through all leaves and to check the shading.
///\sa ShadingEffectOfLeaf
template <class TS, class BUD,class S= Ellipse>
class EvaluateRadiationForHwTreeSegment {
public:
  void operator()(TS* ts)const;
  void setExtinction(ParametricCurve& K); //not needed really for
 //hardwoods, included only to quarantee that program compiles also in
 //the case when constructor of WrapRadiationEvaluations<F,TS,BUD> is
 //invoked with sring argument for harrdwoods.
};

///\brief Evaluate shading caused by all leaves
///
///Evaluate shading caused by all leaves of a hardwood segment
///on a leaf (shaded_l) of a hardwood segment (shaded_s). 
template <class TS,class BUD,class S=Ellipse>
class ShadingEffectOfLeaf{
public:
  ShadingEffectOfLeaf(HwTreeSegment<TS,BUD,S>* ts, BroadLeaf<S>* lf);
  vector<LGMdouble>& operator()(vector<LGMdouble>& v,TreeCompartment<TS,BUD>* tc)const;

  HwTreeSegment<TS,BUD,S>* shaded_s;
  BroadLeaf<S>* shaded_l;
};


///\brief Evaluate radiation climate for conifer segment
///
///Evaluates shading caused by all other segments on this conifer segment.
///This functor uses functor ShadingEffectOfCfTreeSegment to go through all
///segments to check the shading.
///\sa ShadingEffectOfCfTreeSegment 
template <class TS, class BUD>
class EvaluateRadiationForCfTreeSegment {
public:
  EvaluateRadiationForCfTreeSegment(const ParametricCurve& k):K(k){}
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
private:
  const ParametricCurve& K;
};

///\brief Evaluate forest radiation climate for conifer segment
///
///Analogous to EvaluateRadiationForCfTreeSegment but instead of
///Firmament::diffuseRegionRadiationSum uses Firmament::diffuseForestRegionRadiationSum,
///that is, the tree is surrounded by identical trees that are taken
///care with Lambert-Beer extinction.
///The tree level input parameters for diffuseForestRegionRadiationSum
///(needle area, extinction coefficient, tree height, height of
///crown base, stand density, and location of tree (for calculation of
/// distance from tree stem)) are specified in the constructor.
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



///\brief Shading of one conifer segment
///
///Evaluate shading caused by the conifer segment \p tc on the \p shaded_s segment
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



///\brief Shading by woody parts only with self-shading
///
///Two versions: ShadingEffectOfWoodyPartsSelf and ShadingEffectOfWoodyParts.
///
///ShadingEffectOfWoodyPartsSelf should be used to check self-shading by
///woody parts: this takes the target_segment (in the constructor) and checks that comparison
///is not made itself as a shading TreeSegment. Consequently, the shading tree must be consisting of
///similar TreeSegments and Buds (<TS,BUD>) as the target one. Can thus be used for self-
///wood shading and wood-shading by other similar trees.
///\sa ShadingEffectOfWoodyParts
template <class TS,class BUD>
class ShadingEffectOfWoodyPartsSelf {
public:
  ShadingEffectOfWoodyPartsSelf(TreeSegment<TS,BUD>* ts, 
			       vector<double>& sectors)
    :shaded_s(ts), S(sectors){}
  //ForEach functor to compute shadiness
  TreeCompartment<TS,BUD>*  operator()(TreeCompartment<TS,BUD>* tc)const;
  //Get vector for S (shadiness) 
  vector<double>& getS(){return S;}
private:
  TreeSegment<TS,BUD>* shaded_s;
  vector<double>& S;
};

template <class TS,class BUD>
class ShadingEffectOfWoodyPartsSelfConifer {
public:
  ShadingEffectOfWoodyPartsSelfConifer(TreeSegment<TS,BUD>* ts, 
			       vector<double>& sectors)
    :shaded_s(ts), S(sectors){}
  //ForEach functor to compute shadiness
  TreeCompartment<TS,BUD>*  operator()(TreeCompartment<TS,BUD>* tc)const;
  //Get vector for S (shadiness) 
  vector<double>& getS(){return S;}
private:
  TreeSegment<TS,BUD>* shaded_s;
  vector<double>& S;
};

///\brief Shading by woody parts only with no self-shading
///
///Two versions: ShadingEffectOfWoodyPartsSelf and ShadingEffectOfWoodyParts.
//
///ShadingEffectOfWoodyParts Takes a cxxadt::Point (e.g. midpoint of a TreeSegment) in the
///constructor and makes comparisons for that. No checking is made (is not possible) whether the
///shading TreeSegment is the object (e.g. TreeSegment) for which evaluation is made. Can
///thus *not* be used to evaluate self wood shading in a tree.
///\note Assumes that all trees have the same Firmament.
///\sa ShadingEffectOfWoodyPartsSelf
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

template <class TS,class BUD>
class ShadingEffectOfWoodyPartsConifer {
public:
  ShadingEffectOfWoodyPartsConifer(Point tl, 
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















