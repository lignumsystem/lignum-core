#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>
//#include <TreeCompartment.h>




using namespace cxxadt;

namespace Lignum{



template <class TS,class BUD=DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{

#ifdef _MSC_VER   
  friend Bud<TS,BUD>* GetTerminatingBud(const Axis<TS,BUD>& axis);   
  friend std::list<TreeCompartment<TS,BUD>*>& GetTreeCompartmentList(Axis<TS,BUD>& axis);
  friend void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts);
  friend void InsertTreeCompartmentSecondLast(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts); 
  friend TreeCompartment<TS,BUD>* GetFirstTreeCompartment(Axis<TS,BUD>& axis);
  friend TreeSegment<TS, BUD>* GetFirstTreeSegment(Axis<TS,BUD>& axis);
  friend TreeSegment<TS, BUD>* GetLastTreeSegment(Axis<TS,BUD>& axis);
  friend LGMdouble GetSumValue(Axis<TS,BUD>& axis, LGMAD name, int Age=-1);
#else
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

#endif // _MFC_VER


public:
  virtual ~Axis();
  Axis();
  Axis(const Point& p, const PositionVector& d, Tree<TS,BUD>* t);
  
protected: 
  std::list<TreeCompartment<TS,BUD>*> tc_ls;
};




}//closing namespace Lignum

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
