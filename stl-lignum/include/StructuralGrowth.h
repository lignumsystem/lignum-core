#ifndef STRUCTURALGROWTH_H
#define STRUCTURALGROWTH_H

#include <GCTree.h>

namespace Lignum{

class StructureAdjustment{
public:
  StructureAdjustment(Point p, bool b)
    {
      changed = b;
      location = p;
    }
  StructureAdjustment& operator = (const StructureAdjustment& sa)
    {
      changed = sa.changed;
      location = sa.location;
      return *this;
    }

  bool changed;
  Point location;
};


template <class TS,class BUD>
class AdjustStructureAfterZbrent{
public:
  TreeCompartment<TS,BUD>*
  operator ()(StructureAdjustment& sa, TreeCompartment<TS,BUD>* tc)const;
};



template <class TS,class BUD>
class BranchBending
{
public:
  TreeCompartment<TS,BUD>* operator ()(Point &position, TreeCompartment<TS,BUD>* tc)const;
  BranchBending(LGMdouble a) { angleRad = 2.0*PI_VALUE *a /360.0; } 
  LGMdouble angleRad;
};



template <class TS,class BUD>
class FoliageLoss
{
public:
  TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
};

    
}  
  
#include <StructuralGrowthI.h>


#endif

