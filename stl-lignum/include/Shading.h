#ifndef SHADING_H
#define SHADING_H

#include <Tree.h>
#include <BetulaWithFlow.h>
//#include <Algorithms.h>
using namespace Lignum;


//Evaluate radiaton conditions for each leaf
template <class TS,class BUD = DefaultBud<TS> >
class EvaluateRadiation:
  public AdaptableTCFunction<TS,BUD> {
public:
TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >* operator()
  (TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >* tc)const;
};

//Accumulate the effect of shading by other leaves
template <class TS,class BUD = DefaultBud<TS> >
class EvaluateRadiationForLeaf{
public:
  EvaluateRadiationForLeaf(Lignum::BetulaWithFlow* ts, BroadLeaf* lf);
  vector<LGMdouble>& operator()(vector<LGMdouble>& v,
TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >* tc)const;

  Lignum::BetulaWithFlow* shaded_s;
  BroadLeaf* shaded_l;
};

template <class TS,class BUD = DefaultBud<TS> >
class EvaluateRadiationForSegmentCylinder{
};

template <class TS,class BUD = DefaultBud<TS> >
class PrintLight:
  public AdaptableTCFunction<Lignum::BetulaWithFlow,
  DefaultBud<Lignum::BetulaWithFlow> > {
public:
TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >* operator()
  (TreeCompartment<Lignum::BetulaWithFlow,DefaultBud<Lignum::BetulaWithFlow> >* tc)const;
};

#include <ShadingI.h>

#endif





