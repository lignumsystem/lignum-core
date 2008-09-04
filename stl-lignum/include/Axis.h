#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
#include <TreeCompartment.h>
#include <TreeFunctor.h>




using namespace cxxadt;

namespace Lignum{

  class AxisAttributes{
  public:
    AxisAttributes(LGMdouble s):state(s){ }
      LGMdouble state; //ALIVE or DEAD 
  };

template <class TS,class BUD=DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{

  template <class TS1,class BUD1>
  friend Bud<TS1,BUD1>* GetTerminatingBud(const Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend list<TreeCompartment<TS1,BUD1>*>& GetTreeCompartmentList(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend void InsertTreeCompartment(Axis<TS1,BUD1>& axis, TreeCompartment<TS1,BUD1>* ts);
  template <class TS1,class BUD1>
  friend void InsertTreeCompartmentSecondLast(Axis<TS1,BUD1>& axis, 
					      TreeCompartment<TS1,BUD1>* ts); 
  template <class TS1,class BUD1>
  friend TreeCompartment<TS1,BUD1>* GetFirstTreeCompartment(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend TreeSegment<TS1, BUD1>* GetLastTreeSegment(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend TreeSegment<TS1, BUD1>* GetFirstTreeSegment(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend LGMdouble GetSumValue(Axis<TS1,BUD1>& axis, LGMAD name, int Age);
  template <class TS1,class BUD1>
  friend void Delete2ndLastTreeCompartment(Axis<TS1,BUD1>& axis);
  template <class TS1,class BUD1>
  friend LGMdouble GetValue(Axis<TS1,BUD1>& axis, LGMAD name);
  template <class TS1,class BUD1>
  friend LGMdouble SetValue(Axis<TS1,BUD1>& axis, LGMAD name, const LGMdouble value);
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchFoliage(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend int GetNumberOfCompartments(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchSapwoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchHeartwoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchWoodMass(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchPhotosynthesis(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend LGMdouble GetBranchRespiration(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend int GetAxisNumber(Axis<TS1,BUD1>& axis); 
  template <class TS1,class BUD1>  
  friend int SetAxisNumber(Axis<TS1,BUD1>& axis, int number); 

public:
  virtual ~Axis();
  Axis();
  Axis(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  Axis(Tree<TS,BUD>* t):TreeCompartment<TS,BUD>(t),aa(ALIVE), axis_number(0){ }
protected: 
  AxisAttributes aa;
  list<TreeCompartment<TS,BUD>*> tc_ls;
  int axis_number;
};




}//closing namespace Lignum

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
