#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <Tree.h>
#include <Algorithms.h>

//A functor to print out the datatype
//of a tree compartment
template <class TS,class BUD=DefaultBud<TS> >
class DisplayType{
public:
  void operator ()(TreeCompartment<TS,BUD>* ts);
};

template <class TS,class BUD=DefaultBud<TS> >
class DisplayType2: public AdaptableTCFunction<TS,BUD>{
public:
   TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* ts)const;
};

template <class TS,class BUD=DefaultBud<TS> >
class CountTreeSegments{
public:
  int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
};

template <class TS,class BUD=DefaultBud<TS> >
class FillWithWater:  public AdaptableTCFunction<TS,BUD>{
public:
  TreeCompartment<TS,BUD>* operator()(TreeCompartment<TS,BUD>* tc)const;
};


template <class TS,class BUD=DefaultBud<TS> >
class CountCompartments{
public:
  int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
};



template <class TS,class BUD=DefaultBud<TS> >
class CountCompartmentsReverse{
public:
  int& operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
};

template <class TS,class BUD=DefaultBud<TS> >
class MyExampleSignal{
public:
  TreeCompartment<TS,BUD>* operator ()(int& id,TreeCompartment<TS,BUD>* ts)const;
};

template <class TS,class BUD=DefaultBud<TS> >
class DisplayStructure:public AdaptableTCFunction<TS,BUD>{
public:
  int& operator ()(int&,TreeCompartment<TS,BUD>* ts)const;
};
/*
class CountElements{
public:
  void operator ()TreeCompartment<TS>* ts);

}
*/
#endif

