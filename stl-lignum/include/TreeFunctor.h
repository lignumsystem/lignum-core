#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <Tree.h>

//A functor to print out the datatype
//of a tree compartment
template <class TS>
class DisplayType{
public:
  void operator ()(TreeCompartment<TS>* ts);
}; 

#endif

