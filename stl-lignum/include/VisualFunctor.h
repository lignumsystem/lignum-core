#ifndef VISUALFUNCTOR_H
#define VISUALFUNCTOR_H

#include <vector>
#include <Point.h>

namespace Lignum{

template <class TS, class BUD>
class GUS{
public:
  GUS(int init = 0):flag(init){}  
  int flag;
  Point point;
  vector<TreeSegment<TS,BUD>*> v;
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

template <class TS,class BUD>
  class SampleFoliageMass{
  public:
  SampleFoliageMass(KGC f):fm(f){}
  KGC& operator()(KGC& fm, TreeCompartment<TS,BUD>* tc)const;
  KGC fm;
};

template <class T> 
 class SubtractFoliage{
 public:
  SubtractFoliage(const T f):sub(f){}
  T operator()(const T t1, const T t2)const{return t2 - sub;}
  T sub;
};
   
} //closing namespace Lignum

#include <VisualFunctorI.h>

#endif




