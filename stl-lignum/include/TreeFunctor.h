#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <TreeCompartment.h>

class Prod{
public:
  void operator ()(TreeCompartment *tc){tc->Production();}
};

class GetProd{
public:
  TP operator()(TP id,TreeCompartment *tc){return id + tc->GetProduction();}
};

#endif

