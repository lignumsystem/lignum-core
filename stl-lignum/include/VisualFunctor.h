#ifndef VISUALFUNCTOR_H
#define VISUALFUNCTOR_H

#include <vector>
#include <Point.h>

template <class TS, class BUD>
class GUS{
public:
  GUS(int init = 0):flag(init){}  
  int flag;
  Point<METER> point;
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

#include <VisualFunctorI.h>

#endif
