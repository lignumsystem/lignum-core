#ifndef AXIS_H
#define AXIS_H

#include <list>
#include <Point.h>
#include <PositionVector.h>
#include <LGMdecl.h>


namespace Lignum{

using namespace cxxadt;
template <class TS,class BUD = DefaultBud<TS> >
Bud<TS,BUD>* GetTerminatingBud(const Axis<TS,BUD>& axis);
template <class TS,class BUD = DefaultBud<TS> >
list<TreeCompartment<TS,BUD>*>& GetTreeCompartmentList(Axis<TS,BUD>& axis);
template <class TS,class BUD = DefaultBud<TS> >
void InsertTreeCompartment(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts);
template <class TS,class BUD = DefaultBud<TS> >
class Axis: public TreeCompartment<TS,BUD>{
  friend Bud<TS,BUD>* GetTerminatingBud<TS,BUD>(const Axis<TS,BUD>& axis);
  friend list<TreeCompartment<TS,BUD>*>& GetTreeCompartmentList<TS,BUD>(Axis<TS,BUD>& axis);
  friend void InsertTreeCompartment<TS,BUD>(Axis<TS,BUD>& axis, TreeCompartment<TS,BUD>* ts);
public:
  virtual ~Axis();
  Axis();
  Axis(const Point<METER>& p, const PositionVector& d, Tree<TS,BUD>* t);
private:
  list<TreeCompartment<TS,BUD>*> tc_ls;
};

}//closing namespace Lignum

//The implementations of methods and functions Axis
#include <AxisI.h>

#endif
