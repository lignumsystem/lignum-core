#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <Tree.h>

template <class TS>
class DisplayType{
public:
  void operator ()(TreeCompartment<TS>* ts);
}; 

#endif

