#ifndef TREEFUNCTOR_H
#define TREEFUNCTOR_H

#include <iostream>

#include <TreeCompartment.h>
#include <Algorithms.h>

namespace Lignum{

class InfoStruct
{
public:
//      inline InfoStruct& operator += (const InfoStruct& st1);

        int age;
        LGMdouble sum_Wf;
        LGMdouble sum_Qabs;
        int num_buds;
        int num_segments;
        LGMdouble height;
        LGMdouble bottom_rad;
        std::vector<LGMdouble> taper_rad;
        std::vector<LGMdouble> taper_hei;
};

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


template <class TS, class BUD>
Point GetBoundingBox(Tree<TS,BUD> &tree, Point &p);


template <class TS, class BUD>
Point GetBoundingBox(Axis<TS,BUD> &ax, Point &p);



//This class holds the values of the coordinates that define box that
//holds the tree - or several trees.

class BoundingBox { 
 public:
  BoundingBox() { minxyz = Point(R_HUGE, R_HUGE, R_HUGE); 
  maxxyz = Point(-R_HUGE, -R_HUGE, -R_HUGE); }
  Point getMin() { return minxyz; }
  Point getMax() { return maxxyz; }
  void setMinX(const LGMdouble x) { minxyz.setX(x); }
  void setMinY(const LGMdouble y) { minxyz.setY(y); }
  void setMinZ(const LGMdouble z) { minxyz.setZ(z); }
  void setMaxX(const LGMdouble x) { maxxyz.setX(x); }
  void setMaxY(const LGMdouble y) { maxxyz.setY(y); }
  void setMaxZ(const LGMdouble z) { maxxyz.setZ(z); }
 private:
  Point minxyz;
  Point maxxyz;
};


//This functor runs (Accumulate) through tree and finds the bounding
//box for it

template <class TS,class BUD>
class FindBoundingBox{
public:
  BoundingBox& operator ()(BoundingBox& b_box,
				       TreeCompartment<TS,BUD>* tc)const;
};



template <class TS,class BUD>
class TreeHeight
{
public:
  LGMdouble& operator ()(LGMdouble& max_height, TreeCompartment<TS,BUD>* tc)const;
  
};



template <class TS,class BUD>
class CollectFoliageMass
{ 
public:
        LGMdouble& operator()(LGMdouble &sum, TreeCompartment<TS,BUD>* tc)const;
};


template <class TS,class BUD>
class TreeInfo
{ 
public:
        InfoStruct& operator()(InfoStruct &stru, TreeCompartment<TS,BUD>* tc)const;
};



}//closing namespace Lignum
#include <TreeFunctorI.h>

#endif

