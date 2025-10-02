/// \file VisualFunctor.h
/// \brief Obsolete
#ifndef VISUALFUNCTOR_H
#define VISUALFUNCTOR_H

#include <vector>
#include <Point.h>
#include <LGMUnits.h>
#include <LGMdecl.h>

namespace Lignum{

template <class TS, class BUD>
class GUS{
public:
  GUS(int init = 0):flag(init){}  
  int flag;
  Point point;
  std::vector<TreeSegment<TS,BUD>*> v;
};

template <class TS,class BUD>
class GetUpperSegment{
public:
  GUS<TS,BUD>& operator()(GUS<TS,BUD>& gus,TreeCompartment<TS,BUD>* tc)const;
};


template <class TS, class BUD>
class GLS{
public:
  GLS(int init = 0){current=NULL;segment = NULL;} 
  TreeSegment<TS,BUD> *current; 
  TreeSegment<TS,BUD> *segment;
};

template <class TS,class BUD>
class GetLowerSegment{
public:
  GLS<TS,BUD>& operator()(GLS<TS,BUD>& gls,TreeCompartment<TS,BUD>* tc)const;
};

template <class TS,class BUD>
class SampleDiameterGrowth{
public:
  METER& operator()(METER& r,TreeCompartment<TS,BUD>* tc)const;
};


} //closing namespace Lignum

#include <VisualFunctorI.h>

#endif





