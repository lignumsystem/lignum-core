#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <Tree.h>
#include <Algorithms.h>

//A functor to print out the datatype
//of a tree compartment
template <class TS>
class DisplayType{
public:
  void operator ()(TreeCompartment<TS>* ts);
};

template <class TS>
class DisplayType2: public AdaptableTCFunction<TS>{
public:
   TreeCompartment<TS>* operator ()(TreeCompartment<TS>* ts)const;
};

template <class TS>
class CountCompartments{
public:
  void operator ()(int& id,TreeCompartment<TS>* ts)const;
};

template <class TS>
class CountCompartmentsReverse{
public:
  void operator ()(int& id,TreeCompartment<TS>* ts)const;
};

template <class TS>
class MyExampleSignal{
public:
  void operator ()(int& id,TreeCompartment<TS>* ts)const;
};

/*
class CountElements{
public:
  void operator ()TreeCompartment<TS>* ts);

}
*/
#endif

