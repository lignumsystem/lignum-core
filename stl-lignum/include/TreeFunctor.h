#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <iostream>

#include <TreeCompartment.h>
#include <Algorithms.h>

namespace Lignum{

//A functor to print out the datatype
//of a tree compartment
template <class TS,class BUD=DefaultBud<TS> >
class DisplayType{
public:
  TreeCompartment<TS,BUD>*  operator ()(TreeCompartment<TS,BUD>* ts)const;
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

template <class TS,class BUD> void DisplayStructure(Tree<TS,BUD>& t);
template <class TS,class BUD> void DisplayStructure(TreeCompartment<TS,BUD>* tc);

class DisplayStructureData{
public:
  DisplayStructureData()
    :first_segment(true),number_of_compartments(0){}
  bool first_segment;
  int number_of_compartments;
};
    
template <class TS,class BUD=DefaultBud<TS> >
class DisplayStructureFunctor{
public:
  TreeCompartment<TS,BUD>* operator ()(DisplayStructureData& id,
				       TreeCompartment<TS,BUD>* ts)const;


};

template <class TS,class BUD=DefaultBud<TS> >
class CheckCoordinates{
public:
  CheckCoordinates(double e = 1.0e-20);
  TreeCompartment<TS,BUD>* operator ()(Point& id,
				       TreeCompartment<TS,BUD>* ts)const;
  double epsilon;

};
}//closing namespace Lignum
#include <TreeFunctorI.h>

#endif

